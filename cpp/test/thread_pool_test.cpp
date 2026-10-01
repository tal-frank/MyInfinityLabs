#include <iostream>
#include <cassert>
#include <atomic>
#include <chrono>
#include <thread>
#include <memory>
#include <vector>

#include "thread_pool.hpp"

using namespace ilrd_178;

// 1. Basic Task Execution
void TestBasicTaskExecution()
{
    ThreadPool pool(2);
    bool executed = false;

    std::function<void()> func = [&executed]() {
        executed = true;
    };

    std::shared_ptr<ThreadPool::Task> task(new ThreadPool::FunctionTask(func));
    pool.AddTask(task, ThreadPool::NORMAL);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    assert(executed && "Basic task execution failed!");
    std::cout << "[PASS] TestBasicTaskExecution\n";
}

// 2. Multi-threaded Concurrent Execution
void TestConcurrentExecution()
{
    const size_t num_threads = 4;
    const size_t num_tasks = 100;

    ThreadPool pool(num_threads);
    std::atomic<int> counter(0);

    std::function<void()> func = [&counter]() {
        counter.fetch_add(1, std::memory_order_relaxed);
    };

    for (size_t i = 0; i < num_tasks; ++i)
    {
        std::shared_ptr<ThreadPool::Task> task(new ThreadPool::FunctionTask(func));
        pool.AddTask(task, ThreadPool::NORMAL);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    assert(counter.load() == static_cast<int>(num_tasks) && "Concurrent execution failed!");
    std::cout << "[PASS] TestConcurrentExecution\n";
}

// 3. FutureTask Execution with Output Capture
// void TestFutureTaskExecution()
// {
//     ThreadPool pool(2);
//     int result = 0;

//     std::function<int()> func = []() {
//         return 42;
//     };

//     std::shared_ptr<ThreadPool::Task> future_task(
//         new ThreadPool::FutureTask<int>(func, result, ThreadPool::HIGH)
//     );

//     pool.AddTask(future_task, ThreadPool::HIGH);

//     std::this_thread::sleep_for(std::chrono::milliseconds(50));

//     assert(result == 42 && "FutureTask result execution failed!");
//     std::cout << "[PASS] TestFutureTaskExecution\n";
// }

// 4. Exception Handling Resilience
void TestExceptionHandling()
{
    ThreadPool pool(2);
    bool next_executed = false;

    std::function<void()> throwing_func = []() {
        throw std::runtime_error("Expected test error");
    };

    std::function<void()> safe_func = [&next_executed]() {
        next_executed = true;
    };

    std::shared_ptr<ThreadPool::Task> bad_task(new ThreadPool::FunctionTask(throwing_func));
    std::shared_ptr<ThreadPool::Task> good_task(new ThreadPool::FunctionTask(safe_func));

    pool.AddTask(bad_task, ThreadPool::HIGH);
    pool.AddTask(good_task, ThreadPool::NORMAL);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    assert(next_executed && "Worker thread died on task exception!");
    std::cout << "[PASS] TestExceptionHandling\n";
}

int main()
{
    std::cout << "Starting C++11 ThreadPool Unit Tests...\n";

    TestBasicTaskExecution();
    TestConcurrentExecution();
    // TestFutureTaskExecution();
    TestExceptionHandling();

    std::cout << "\nAll C++11 unit tests passed successfully!\n";
    return 0;
}

// #include "thread_pool.hpp"

// using namespace ilrd_178;
// int main()
// {
//     ThreadPool TP(10);

//     return 0;
// }