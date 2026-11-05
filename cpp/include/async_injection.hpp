#ifndef ILRD_178_ASYNC_INJECTION
#define ILRD_178_ASYNC_INJECTION

#include <chrono>     // milliseconds
#include <functional> // std::function

#include "scheduler.hpp"

namespace ilrd_178
{

class AsyncInjection
{
public:
    AsyncInjection(std::function<bool(void)> callable, 
                   std::chrono::milliseconds time_to_exec_ms);

    AsyncInjection(const AsyncInjection& other) = delete;
    AsyncInjection& operator=(const AsyncInjection& other) = delete;
    
private:
    ~AsyncInjection() = default;

    class Task : public Scheduler::ISchedulerTask
    {
    public:
        Task(AsyncInjection* async_injection);
        void Execute() override;
    private:
        AsyncInjection* m_async_injection;
    };

    std::function<bool(void)> m_callable;
    std::chrono::milliseconds m_time_to_exec_ms;
};

}

#endif