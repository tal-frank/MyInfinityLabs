#include <waitable_queue.hpp>

#include <iostream>             // cout
#include <thread>               // thread
#include <vector>               // vector
#include <atomic>               // atomic
#include <chrono>               // milliseconds, steady_clock
#include <mutex>                // mutex, lock_guard
#include "waitable_queue.hpp"   // API

using namespace std;
using namespace ilrd_178;
using namespace std::chrono;

static int g_failures = 0;

static void Check(bool cond, const char *msg)
{
    ::cout << (cond ? "\033[32m[PASS]\033[0m " : "\033[31m[FAIL]\033[0m ")
           << msg << ::endl;
    if (!cond)
    {
        ++g_failures;
    }
}

static long ElapsedMs(steady_clock::time_point start)
{
    return duration_cast<milliseconds>(steady_clock::now() - start).count();
}

//---------------------------- single thread ------------------------------//

static void TestEmpty()
{
    WaitableQueue<int> wq;
    Check(wq.IsEmpty(), "new queue is empty");

    wq.Push(1);
    Check(!wq.IsEmpty(), "queue not empty after Push");

    int x = 0;
    wq.Pop(x);
    Check(wq.IsEmpty(), "queue empty after Pop");
}

static void TestFifoOrder()
{
    WaitableQueue<int> wq;
    for (int i = 0; i < 10; ++i)
    {
        wq.Push(i);
    }

    bool in_order = true;
    for (int i = 0; i < 10; ++i)
    {
        int x = -1;
        wq.Pop(x);
        in_order = in_order && (x == i);
    }
    Check(in_order, "Pop returns elements in FIFO order");
}

static void TestTimeoutOnEmpty()
{
    WaitableQueue<int> wq;
    int x = 42;

    steady_clock::time_point start = steady_clock::now();
    bool ret = wq.Pop(x, milliseconds(200));
    long ms = ElapsedMs(start);

    Check(!ret, "timed Pop on empty queue returns false");
    Check(x == 42, "timed Pop failure leaves dest untouched");
    Check(ms >= 200 && ms < 400, "timed Pop waits ~timeout before failing");
}

static void TestPushBeforePop()
{
    // regression: an element pushed before the wait must not be missed
    WaitableQueue<int> wq;
    wq.Push(7);

    int x = 0;
    steady_clock::time_point start = steady_clock::now();
    bool ret = wq.Pop(x, milliseconds(1000));

    Check(ret && x == 7, "timed Pop finds element pushed earlier");
    Check(ElapsedMs(start) < 100, "timed Pop returns immediately if not empty");
}

//---------------------------- multi thread -------------------------------//

static void TestBlockingPopWaits()
{
    WaitableQueue<int> wq;
    int x = 0;

    steady_clock::time_point start = steady_clock::now();
    thread producer([&wq]
    {
        this_thread::sleep_for(milliseconds(200));
        wq.Push(5);
    });

    wq.Pop(x);
    long ms = ElapsedMs(start);
    producer.join();

    Check(x == 5, "blocking Pop gets element from other thread");
    Check(ms >= 150, "blocking Pop actually waited for the Push");
}

static void TestTimedPopWakesOnPush()
{
    WaitableQueue<int> wq;
    int x = 0;

    thread producer([&wq]
    {
        this_thread::sleep_for(milliseconds(100));
        wq.Push(9);
    });

    steady_clock::time_point start = steady_clock::now();
    bool ret = wq.Pop(x, milliseconds(2000));
    long ms = ElapsedMs(start);
    producer.join();

    Check(ret && x == 9, "timed Pop succeeds when Push arrives in time");
    Check(ms < 1000, "timed Pop wakes on Push, not on timeout");
}

static void TestManyProducersConsumers()
{
    const int PRODUCERS = 4;
    const int CONSUMERS = 4;
    const int PER_PRODUCER = 1000;
    const int TOTAL = PRODUCERS * PER_PRODUCER;

    WaitableQueue<int> wq;
    vector<int> seen(TOTAL, 0);
    mutex seen_mtx;
    atomic<int> popped(0);

    vector<thread> threads;
    for (int p = 0; p < PRODUCERS; ++p)
    {
        threads.emplace_back([&wq, p, PER_PRODUCER]
        {
            for (int i = 0; i < PER_PRODUCER; ++i)
            {
                wq.Push(p * PER_PRODUCER + i);
            }
        });
    }

    for (int c = 0; c < CONSUMERS; ++c)
    {
        threads.emplace_back([&]
        {
            int x = 0;
            // stop once nothing arrives for a while
            while (wq.Pop(x, milliseconds(300)))
            {
                lock_guard<mutex> lock(seen_mtx);
                ++seen[x];
                ++popped;
            }
        });
    }

    for (thread& t : threads)
    {
        t.join();
    }

    bool each_once = true;
    for (int i = 0; i < TOTAL; ++i)
    {
        each_once = each_once && (seen[i] == 1);
    }

    Check(popped == TOTAL, "all pushed elements were popped");
    Check(each_once, "every element popped exactly once");
    Check(wq.IsEmpty(), "queue empty after producers/consumers finish");
}

static void TestMoreConsumersThanItems()
{
    // 2 items, 5 waiting consumers: exactly 2 succeed, 3 time out
    WaitableQueue<int> wq;
    atomic<int> succeeded(0);
    atomic<int> timed_out(0);

    vector<thread> consumers;
    for (int i = 0; i < 5; ++i)
    {
        consumers.emplace_back([&]
        {
            int x = 0;
            if (wq.Pop(x, milliseconds(500)))
            {
                ++succeeded;
            }
            else
            {
                ++timed_out;
            }
        });
    }

    this_thread::sleep_for(milliseconds(100));
    wq.Push(1);
    wq.Push(2);

    for (thread& t : consumers)
    {
        t.join();
    }

    Check(succeeded == 2 && timed_out == 3,
          "extra consumers time out instead of popping an empty queue");
}

int main()
{
    TestEmpty();
    TestFifoOrder();
    TestTimeoutOnEmpty();
    TestPushBeforePop();
    TestBlockingPopWaits();
    TestTimedPopWakesOnPush();
    TestManyProducersConsumers();
    TestMoreConsumersThanItems();

    if (0 == g_failures)
    {
        ::cout << "\n\033[32mAll tests passed\033[0m\n";
    }
    else
    {
        ::cout << "\n\033[31m" << g_failures << " test(s) failed\033[0m\n";
    }

    return g_failures;
}