#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <cassert>

#include "singleton.hpp"
#include "scheduler.hpp"

// Assuming Google Test (gtest) or similar assertions, 
// but written here with standard assertions/atomic flags for clarity and standalone use.

class MockTask : public ilrd_178::Scheduler::ISchedulerTask
{
public:
    MockTask(int id, std::atomic<int>& execution_counter, std::vector<int>& execution_order)
        : m_id(id), m_counter(execution_counter), m_order(execution_order) {}

    void Execute() override
    {
        m_order.push_back(m_id);
        m_counter++;
    }

private:
    int m_id;
    std::atomic<int>& m_counter;
    std::vector<int>& m_order;
};

// Test 1: Single Task Execution
void TestSingleTaskExecution()
{
    std::cout << "[TEST] Running TestSingleTaskExecution...\n";
    
    std::atomic<int> counter{0};
    std::vector<int> order;

    auto& scheduler = Singleton<ilrd_178::Scheduler>::GetInstance();

    auto task = std::make_shared<MockTask>(1, counter, order);
    scheduler.AddTask(task, std::chrono::milliseconds(100));

    // Wait enough time for the task to execute
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    assert(counter == 1);
    assert(order.size() == 1);
    assert(order[0] == 1);

    std::cout << "[TEST] TestSingleTaskExecution Passed!\n";
}

// Test 2: Priority Ordering (Multiple tasks added out of order)
void TestPriorityOrdering()
{
    std::cout << "[TEST] Running TestPriorityOrdering...\n";

    std::atomic<int> counter{0};
    std::vector<int> order;

    auto& scheduler = Singleton<ilrd_178::Scheduler>::GetInstance();

    // Add tasks: Task 3 (300ms), Task 1 (100ms), Task 2 (200ms)
    // Expected execution order: 1 -> 2 -> 3
    scheduler.AddTask(std::make_shared<MockTask>(3, counter, order), std::chrono::milliseconds(300));
    scheduler.AddTask(std::make_shared<MockTask>(1, counter, order), std::chrono::milliseconds(100));
    scheduler.AddTask(std::make_shared<MockTask>(2, counter, order), std::chrono::milliseconds(200));

    // Wait for all tasks to complete
    std::this_thread::sleep_for(std::chrono::milliseconds(450));

    assert(counter == 3);
    assert(order.size() == 3);
    assert(order[0] == 1);
    assert(order[1] == 2);
    assert(order[2] == 3);

    std::cout << "[TEST] TestPriorityOrdering Passed!\n";
}

// Test 3: Preemption / Dynamic Earlier Task Insertion
void TestDynamicPreemption()
{
    std::cout << "[TEST] Running TestDynamicPreemption...\n";

    std::atomic<int> counter{0};
    std::vector<int> order;

    auto& scheduler = Singleton<ilrd_178::Scheduler>::GetInstance();

    // Add a long task first (400ms)
    scheduler.AddTask(std::make_shared<MockTask>(2, counter, order), std::chrono::milliseconds(400));

    // Wait a tiny bit, then insert an earlier task (100ms)
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    scheduler.AddTask(std::make_shared<MockTask>(1, counter, order), std::chrono::milliseconds(100));

    // Expected execution order: Task 1 should preempt and run before Task 2
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    assert(counter == 2);
    assert(order.size() == 2);
    assert(order[0] == 1);
    assert(order[1] == 2);

    std::cout << "[TEST] TestDynamicPreemption Passed!\n";
}

int main()
{
    std::cout << "=== STARTING SCHEDULER TESTS ===\n";

    try {
        TestSingleTaskExecution();
        TestPriorityOrdering();
        TestDynamicPreemption();
        
        std::cout << "\n=== ALL TESTS PASSED SUCCESSFULLY ===\n";
    } catch (const std::exception& e) {
        std::cerr << "[TEST FAILURE] Exception thrown: " << e.what() << "\n";
        return 1;
    }

    return 0;
}