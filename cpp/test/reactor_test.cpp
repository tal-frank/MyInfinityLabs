// #include <iostream>
// #include <cassert>
// #include <unistd.h>
// #include "reactor.hpp"
// #include "selector.hpp"

// using namespace ilrd_178;

// // Test 1: Basic Run and Stop
// void TestRunAndStop()
// {
//     std::cout << "[Test] Running TestRunAndStop..." << std::endl;
//     Select* select_mechanism = new Select();
//     Reactor reactor(select_mechanism);

//     int pipefd[2];
//     assert(pipe(pipefd) == 0);

//     bool callback_executed = false;
//     reactor.Add(pipefd[0], [&]() {
//         char dummy;
//         read(pipefd[0], &dummy, 1);
//         callback_executed = true;
//         reactor.Stop();
//     });

//     // Write to pipe to trigger select
//     char buf = 'A';
//     assert(write(pipefd[1], &buf, 1) == 1);

//     reactor.Run(); // Should block, trigger callback, call Stop(), and return

//     assert(callback_executed);
    
//     close(pipefd[0]);
//     close(pipefd[1]);
//     std::cout << "[Test] TestRunAndStop PASSED." << std::endl;
// }

// // Test 2: Callback removes itself and another callback
// void TestSelfRemoval()
// {
//     std::cout << "[Test] Running TestSelfRemoval..." << std::endl;
//     Select* select_mechanism = new Select();
//     Reactor reactor(select_mechanism);

//     int pipe1[2], pipe2[2];
//     assert(pipe(pipe1) == 0);
//     assert(pipe(pipe2) == 0);

//     bool cb1_called = false;
//     bool cb2_called = false;

//     reactor.Add(pipe1[0], [&]() {
//         char dummy;
//         read(pipe1[0], &dummy, 1);
//         cb1_called = true;
//         std::cout << "CB1 executing, removing self and pipe2..." << std::endl;
//         reactor.Remove(pipe1[0]); // Remove itself
//         reactor.Remove(pipe2[0]); // Remove other callback
//         reactor.Stop();
//     });

//     reactor.Add(pipe2[0], [&]() {
//         char dummy;
//         read(pipe2[0], &dummy, 1);
//         cb2_called = true;
//     });

//     char buf = 'X';
//     // Trigger both pipes
//     assert(write(pipe1[1], &buf, 1) == 1);
//     assert(write(pipe2[1], &buf, 1) == 1);

//     reactor.Run();

//     assert(cb1_called);
//     assert(!cb2_called); // CB2 should be suppressed because CB1 removed it before it ran

//     close(pipe1[0]); close(pipe1[1]);
//     close(pipe2[0]); close(pipe2[1]);
//     std::cout << "[Test] TestSelfRemoval PASSED." << std::endl;
// }

// int main()
// {
//     std::cout << "=== STARTING REACTOR TESTS ===" << std::endl;
//     TestRunAndStop();
//     TestSelfRemoval();
//     std::cout << "=== ALL TESTS PASSED SUCCESSFULLY ===" << std::endl;
//     return 0;
// }

#include <iostream>
#include <cassert>
#include <unistd.h>
#include <stdexcept>
#include "reactor.hpp"
#include "selector.hpp"

using namespace ilrd_178;

// Test 1: Basic Read Run, Stop, and Callback Execution
void TestReadRunAndStop()
{
    std::cout << "[Test] Running TestReadRunAndStop..." << std::endl;
    Select* select_mechanism = new Select();
    Reactor reactor(select_mechanism);

    int pipefd[2];
    assert(pipe(pipefd) == 0);

    bool callback_executed = false;
    reactor.Add({pipefd[0], read_op}, [&]() {
        char dummy;
        read(pipefd[0], &dummy, 1); // Consume the byte
        callback_executed = true;
        reactor.Stop();
    });

    char buf = 'A';
    assert(write(pipefd[1], &buf, 1) == 1);

    reactor.Run();

    assert(callback_executed);
    
    close(pipefd[0]);
    close(pipefd[1]);
    std::cout << "[Test] TestReadRunAndStop PASSED." << std::endl;
}

// Test 2: Write Mode Readiness
void TestWriteMode()
{
    std::cout << "[Test] Running TestWriteMode..." << std::endl;
    Select* select_mechanism = new Select();
    Reactor reactor(select_mechanism);

    int pipefd[2];
    assert(pipe(pipefd) == 0);

    bool write_callback_executed = false;
    reactor.Add({pipefd[1], write_op}, [&]() {
        write_callback_executed = true;
        reactor.Remove({pipefd[1], write_op});
        reactor.Stop();
    });

    reactor.Run();

    assert(write_callback_executed);

    close(pipefd[0]);
    close(pipefd[1]);
    std::cout << "[Test] TestWriteMode PASSED." << std::endl;
}

// Test 3: Multiple calls to Run have defined behavior (throws runtime_error)
void TestMultipleRunCalls()
{
    std::cout << "[Test] Running TestMultipleRunCalls..." << std::endl;
    Select* select_mechanism = new Select();
    Reactor reactor(select_mechanism);

    int pipefd[2];
    assert(pipe(pipefd) == 0);

    reactor.Add({pipefd[0], read_op}, [&]() {
        char dummy;
        read(pipefd[0], &dummy, 1);
        
        // Attempting to call Run() again while already running should throw an exception
        bool exception_thrown = false;
        try {
            reactor.Run();
        } catch (const std::runtime_error& e) {
            exception_thrown = true;
        }
        assert(exception_thrown);

        reactor.Stop();
    });

    char buf = 'B';
    assert(write(pipefd[1], &buf, 1) == 1);

    reactor.Run();

    close(pipefd[0]);
    close(pipefd[1]);
    std::cout << "[Test] TestMultipleRunCalls PASSED." << std::endl;
}

// Test 4: Callback removes itself and another callback, ensuring suppressed callbacks don't run after stop
void TestSelfRemovalAndSuppression()
{
    std::cout << "[Test] Running TestSelfRemovalAndSuppression..." << std::endl;
    Select* select_mechanism = new Select();
    Reactor reactor(select_mechanism);

    int pipe1[2], pipe2[2];
    assert(pipe(pipe1) == 0);
    assert(pipe(pipe2) == 0);

    bool cb1_called = false;
    bool cb2_called = false;

    reactor.Add({pipe1[0], read_op}, [&]() {
        char dummy;
        read(pipe1[0], &dummy, 1);
        cb1_called = true;
        
        reactor.Remove({pipe1[0], read_op}); // Remove self
        reactor.Remove({pipe2[0], read_op}); // Remove other callback
        reactor.Stop();
    });

    reactor.Add({pipe2[0], read_op}, [&]() {
        cb2_called = true;
    });

    char buf = 'X';
    assert(write(pipe1[1], &buf, 1) == 1);
    assert(write(pipe2[1], &buf, 1) == 1);

    reactor.Run();

    assert(cb1_called);
    assert(!cb2_called); // CB2 must not be called because CB1 removed it and called Stop()

    close(pipe1[0]); close(pipe1[1]);
    close(pipe2[0]); close(pipe2[1]);
    std::cout << "[Test] TestSelfRemovalAndSuppression PASSED." << std::endl;
}

int main()
{
    std::cout << "=== STARTING COMPREHENSIVE REACTOR TESTS ===" << std::endl;
    TestReadRunAndStop();
    TestWriteMode();
    TestMultipleRunCalls();
    TestSelfRemovalAndSuppression();
    std::cout << "=== ALL TESTS PASSED SUCCESSFULLY ===" << std::endl;
    return 0;
}