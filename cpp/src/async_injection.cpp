#include "async_injection.hpp"
#include "singleton.hpp"

namespace ilrd_178
{

AsyncInjection::
AsyncInjection(std::function<bool(void)> callable,
               std::chrono::milliseconds time_to_exec_ms) : m_callable(callable),
                                                            m_time_to_exec_ms(time_to_exec_ms)
{
    Scheduler* scheduler = Singleton<Scheduler>::GetInstance();
    std::shared_ptr<Task> task = std::make_shared<Task>(this);
    scheduler->AddTask(task, m_time_to_exec_ms);
}

AsyncInjection::Task::
Task(AsyncInjection *async_injection) : m_async_injection(async_injection) {}

void AsyncInjection::Task::Execute()
{
    if (true == m_async_injection->m_callable())
    {
        delete this->m_async_injection;
    }
    else
    {
        Scheduler* scheduler = Singleton<Scheduler>::GetInstance();
        std::shared_ptr<Task> task_retry = std::make_shared<Task>(m_async_injection);
        scheduler->AddTask(task_retry, m_async_injection->m_time_to_exec_ms);
    }
}

}