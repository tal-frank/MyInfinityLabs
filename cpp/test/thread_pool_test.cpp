// #include <iostream>
// #include <cassert>
// #include <atomic>
// #include <chrono>
// #include <thread>
// #include <memory>
// #include <vector>

// #include "thread_pool.hpp"

// using namespace ilrd_178;

// // 1. Basic Task Execution
// void TestBasicTaskExecution()
// {
//     ThreadPool pool(2);
//     bool executed = false;

//     std::function<void()> func = [&executed]() {
//         executed = true;
//     };

//     std::shared_ptr<ThreadPool::Task> task(new ThreadPool::FunctionTask(func));
//     pool.AddTask(task, ThreadPool::NORMAL);

//     std::this_thread::sleep_for(std::chrono::milliseconds(50));

//     assert(executed && "Basic task execution failed!");
//     std::cout << "[PASS] TestBasicTaskExecution\n";
// }

// // 2. Multi-threaded Concurrent Execution
// void TestConcurrentExecution()
// {
//     const size_t num_threads = 4;
//     const size_t num_tasks = 100;

//     ThreadPool pool(num_threads);
//     std::atomic<int> counter(0);

//     std::function<void()> func = [&counter]() {
//         counter.fetch_add(1, std::memory_order_relaxed);
//     };

//     for (size_t i = 0; i < num_tasks; ++i)
//     {
//         std::shared_ptr<ThreadPool::Task> task(new ThreadPool::FunctionTask(func));
//         pool.AddTask(task, ThreadPool::NORMAL);
//     }

//     std::this_thread::sleep_for(std::chrono::milliseconds(200));

//     assert(counter.load() == static_cast<int>(num_tasks) && "Concurrent execution failed!");
//     std::cout << "[PASS] TestConcurrentExecution\n";
// }

// // // 3. FutureTask Execution with Output Capture
// // void TestFutureTaskExecution()
// // {
// //     ThreadPool pool(2);
// //     int result = 0;

// //     std::function<int()> func = []() {
// //         return 42;
// //     };

// //     std::shared_ptr<ThreadPool::Task> future_task(
// //         new ThreadPool::FutureTask<int>(func, result, ThreadPool::HIGH)
// //     );

// //     pool.AddTask(future_task, ThreadPool::HIGH);

// //     std::this_thread::sleep_for(std::chrono::milliseconds(50));

// //     assert(result == 42 && "FutureTask result execution failed!");
// //     std::cout << "[PASS] TestFutureTaskExecution\n";
// // }

// // 4. Exception Handling Resilience
// void TestExceptionHandling()
// {
//     ThreadPool pool(2);
//     bool next_executed = false;

//     std::function<void()> throwing_func = []() {
//         throw std::runtime_error("Expected test error");
//     };

//     std::function<void()> safe_func = [&next_executed]() {
//         next_executed = true;
//     };

//     std::shared_ptr<ThreadPool::Task> bad_task(new ThreadPool::FunctionTask(throwing_func));
//     std::shared_ptr<ThreadPool::Task> good_task(new ThreadPool::FunctionTask(safe_func));

//     pool.AddTask(bad_task, ThreadPool::HIGH);
//     pool.AddTask(good_task, ThreadPool::NORMAL);

//     std::this_thread::sleep_for(std::chrono::milliseconds(100));

//     assert(next_executed && "Worker thread died on task exception!");
//     std::cout << "[PASS] TestExceptionHandling\n";
// }

// int main()
// {
//     std::cout << "Starting C++11 ThreadPool Unit Tests...\n";

//     TestBasicTaskExecution();
//     TestConcurrentExecution();
//     // TestFutureTaskExecution();
//     TestExceptionHandling();

//     std::cout << "\nAll C++11 unit tests passed successfully!\n";
//     return 0;
// }

/////////////////////////////////////////////////////////////////////////////

// #include "thread_pool.hpp"

// using namespace ilrd_178;
// int main()
// {
//     ThreadPool TP(10);

//     return 0;
// }

/////////////////////////////////////////////////////////////////////////////////

// #include <iostream> // cout
// #include <ostream>
// #include <sstream>  // ostringstream
// #include <unistd.h> // sleep

// #include "thread_pool.hpp"      // API
// // #include "shared_pointer.hpp"   // SharedPtr

// using namespace ilrd_178;
// using namespace std;

// void FastTask()
// {
//     static std::atomic<size_t> i;
//     std::ostringstream line;
//     line << i++ << ": fast task\n";
//     ::cout << line.str();
// }

// void SlowTask()
// {
//     static std::atomic<size_t> i;
//     std::ostringstream line;
//     line << i++ << ": slow task\n";
//     ::cout << line.str();
//     ::sleep(1);
// }

// int main()
// {
//     ThreadPool thpol(0);
//     shared_ptr<ThreadPool::FunctionTask> f_task(
//                                         new ThreadPool::FunctionTask(FastTask));

//     for(size_t i = 0 ; i < 100 ; ++i)
//     {
//         if (50 == i)
//         {
//             thpol.Pause();
//         }
//         thpol.AddTask(f_task, ThreadPool::NORMAL);
//     }

//     size_t ft1_res = 0;
//     size_t ft2_res = 0;
//     size_t ft3_res = 0;

//     std::function<size_t(void)> ft1_lmbda = []() { return size_t(1); };
//     std::function<size_t(void)> ft2_lmbda = []() { return size_t(2); };
//     std::function<size_t(void)> ft3_lmbda = []() { return size_t(3); };

//     shared_ptr<ThreadPool::FutureTask<size_t>> ft1(
//                         new ThreadPool::FutureTask<size_t>(ft1_lmbda, ft1_res));
//     shared_ptr<ThreadPool::FutureTask<size_t>> ft2(
//                         new ThreadPool::FutureTask<size_t>(ft2_lmbda, ft2_res));
//     shared_ptr<ThreadPool::FutureTask<size_t>> ft3(
//                         new ThreadPool::FutureTask<size_t>(ft3_lmbda, ft3_res));

//     thpol.AddTask(ft1, ThreadPool::NORMAL);
//     thpol.AddTask(ft2, ThreadPool::NORMAL);
//     thpol.AddTask(ft3, ThreadPool::NORMAL);

//     ::sleep(3);
//     thpol.Resume();

//     shared_ptr<ThreadPool::FunctionTask> s_task(
//                                         new ThreadPool::FunctionTask(SlowTask));
//     for(size_t i = 0 ; i < 50 ; ++i)
//     {
//         thpol.AddTask(s_task, ThreadPool::NORMAL);
//     }

//     std::ostringstream GetStr;
//     GetStr << "FutureTask->Get() values:" << endl
//            << "ft1: " << ft1->Get() << ::endl
//            << "ft2: " << ft2->Get() << ::endl
//            << "ft3: " << ft3->Get() << ::endl;
//     ::cout << GetStr.str();

//     ::sleep(1);

//     std::ostringstream CachedStr;
//     CachedStr << "FutureTask->Get() cached values:" << endl
//            << "cached ft1: " << ft1->Get() << ::endl
//            << "cached ft2: " << ft2->Get() << ::endl
//            << "cached ft3: " << ft3->Get() << ::endl;
//     ::cout << CachedStr.str();

//     return 0;
// }

///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <functional>

#include "thread_pool.hpp"

using namespace ilrd_178;

// Helper to print test progress
void RunTest(const std::string& test_name, std::function<void()> test_func) 
{
    std::cout << "[RUNNING] " << test_name << "... ";
    test_func();
    std::cout << "PASSED\n";
}

//------------------------------------------------------------------------------
// Construction & Destruction Tests
//------------------------------------------------------------------------------

void TestConstructionAndDestruction() 
{
    {
        ThreadPool pool(4);
    } // Ensure destructor joins threads cleanly

    {
        ThreadPool pool(0);
    }
}

//------------------------------------------------------------------------------
// Basic Task Execution (FunctionTask)
//------------------------------------------------------------------------------

void TestExecuteFunctionTask() 
{
    ThreadPool pool(4);
    std::atomic<bool> executed(false);

    auto task = std::make_shared<ThreadPool::FunctionTask>([&executed]() {
        executed = true;
    });

    pool.AddTask(task, ThreadPool::NORMAL);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    assert(executed.load() == true);
}

void TestExecuteMultipleTasks() 
{
    const int task_count = 100;
    ThreadPool pool(4);
    std::atomic<int> counter(0);

    for (int i = 0; i < task_count; ++i) 
    {
        auto task = std::make_shared<ThreadPool::FunctionTask>([&counter]() {
            counter.fetch_add(1, std::memory_order_relaxed);
        });
        pool.AddTask(task, ThreadPool::NORMAL);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    assert(counter.load() == task_count);
}

//------------------------------------------------------------------------------
// FutureTask Tests
//------------------------------------------------------------------------------

void TestFutureTaskReturnValue() 
{
    ThreadPool pool(2);

    int result = 0;
    std::function<int(void)> compute_func = []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        return 42;
    };

    auto future_task = std::make_shared<ThreadPool::FutureTask<int>>(compute_func, result);
    pool.AddTask(future_task, ThreadPool::HIGH);

    // Get() should block until completed
    int val = future_task->Get();
    assert(val == 42);
    assert(result == 42);
}

//------------------------------------------------------------------------------
// Priority Tests
//------------------------------------------------------------------------------

void TestPriorityExecutionOrder() 
{
    // Start with 0 threads to queue tasks first
    ThreadPool pool(1); 
    std::vector<int> execution_order;
    std::mutex order_mutex;

    auto make_task = [&](int id) {
        return std::make_shared<ThreadPool::FunctionTask>([&execution_order, &order_mutex, id]() {
            std::lock_guard<std::mutex> lock(order_mutex);
            execution_order.push_back(id);
        });
    };
    pool.Pause();
    // Queue in reverse priority order
    pool.AddTask(make_task(3), ThreadPool::LOW);
    pool.AddTask(make_task(2), ThreadPool::NORMAL);
    pool.AddTask(make_task(1), ThreadPool::HIGH);
    pool.Resume();
    // Add 1 worker thread to process popped tasks sequentially
    // pool.SetNumOfThreads(1);
    std::this_thread::sleep_for(std::chrono::milliseconds(150));

    std::lock_guard<std::mutex> lock(order_mutex);
    assert(execution_order.size() == 3);
    // Priority order: HIGH (1) -> NORMAL (2) -> LOW (3)
    assert(execution_order[0] == 1);
    assert(execution_order[1] == 2);
    assert(execution_order[2] == 3);
}

//------------------------------------------------------------------------------
// Pause and Resume Tests
//------------------------------------------------------------------------------

void TestPauseAndResume() 
{
    ThreadPool pool(2);
    std::atomic<int> counter(0);

    pool.Pause();

    for (int i = 0; i < 10; ++i) 
    {
        auto task = std::make_shared<ThreadPool::FunctionTask>([&counter]() {
            counter++;
        });
        pool.AddTask(task, ThreadPool::NORMAL);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    assert(counter.load() == 0); // Must stay paused

    pool.Resume();
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    assert(counter.load() == 10); // Executes after resume
}

//------------------------------------------------------------------------------
// Dynamic Resizing Tests
//------------------------------------------------------------------------------

void TestSetNumOfThreads() 
{
    ThreadPool pool(2);
    std::atomic<int> active_tasks(0);
    std::atomic<int> total_completed(0);

    auto slow_task = [&active_tasks, &total_completed]() {
        active_tasks++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        active_tasks--;
        total_completed++;
    };

    pool.SetNumOfThreads(8);

    for (int i = 0; i < 8; ++i) 
    {
        pool.AddTask(std::make_shared<ThreadPool::FunctionTask>(slow_task), ThreadPool::NORMAL);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    assert(active_tasks.load() > 2); // Confirms scaling up
    pool.SetNumOfThreads(1);


    std::this_thread::sleep_for(std::chrono::milliseconds(300));


    assert(total_completed.load() == 8);
}

//------------------------------------------------------------------------------
// Main Runner
//------------------------------------------------------------------------------

int main() 
{
    std::cout << "================ ThreadPool Unit Tests ================\n";

    RunTest("Construction & Destruction", TestConstructionAndDestruction);
    RunTest("Single Task Execution",      TestExecuteFunctionTask);
    RunTest("Multiple Tasks Execution",    TestExecuteMultipleTasks);
    RunTest("FutureTask Get Return Value", TestFutureTaskReturnValue);
    RunTest("Priority Order Queueing",    TestPriorityExecutionOrder);
    RunTest("Pause and Resume",            TestPauseAndResume);
    RunTest("Dynamic Thread Resizing",    TestSetNumOfThreads);

    std::cout << "================ All Tests Passed! ================\n";
    return 0;
}