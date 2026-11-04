#include <thread>  // thread
#include <csignal>
#include <cstring> // memset

#include "scheduler.hpp"

namespace ilrd_178
{
static void SetItimerspec (std::chrono::steady_clock::time_point time_point, 
                           struct itimerspec& delay);

Scheduler::Scheduler() : m_invoke(false), 
                         m_is_running(true), 
                         m_is_earlier_task(false)
{
    struct sigevent sig_e;
    std::memset(&sig_e, 0, sizeof(sig_e));
    sig_e.sigev_notify = SIGEV_THREAD;
    sig_e.sigev_value.sival_ptr = this;
    sig_e.sigev_notify_function = [] (union sigval sv) 
                            {
                                auto sched = static_cast<Scheduler*>(sv.sival_ptr);
                                {
                                    std::lock_guard<std::mutex> lock(sched->m_mutex);
                                    sched->m_invoke = true;
                                }
                                sched->m_cvar.notify_one();
                            };

    timer_create(CLOCK_REALTIME, &sig_e, &m_timerid);
    m_thread.reset(new std::thread([this]()
                            {
                                while(m_is_running)
                                {
                                    m_tasks.Pop(m_curr_task);

                                    {
                                        std::unique_lock<std::mutex> lock(m_mutex);
                                        m_invoke = false;
                                        m_is_earlier_task = false;
                                        struct itimerspec delay;
                                        SetItimerspec(m_curr_task->m_exec_time_ms, delay);
                                        timer_settime(m_timerid, 0, &delay, nullptr);
                                        m_cvar.wait(lock, [this] { return m_invoke ||
                                                                          m_is_earlier_task ||
                                                                          !m_is_running;});
                                    }
                                    
                                    if (std::chrono::steady_clock::now() < 
                                        m_curr_task->m_exec_time_ms)
                                    {
                                        m_tasks.Push(m_curr_task);
                                        continue;
                                    }

                                    try
                                    {
                                        m_curr_task->m_schedTask->Execute();
                                    }
                                    catch(...) {}
                                }
                            }));
}

Scheduler::~Scheduler()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_is_running = false;
    }

    m_cvar.notify_one();

    try
    {
        AddTask(std::make_shared<PoisonPill>(), std::chrono::milliseconds(0));
    }
    catch(...) {}
    
    if (m_thread->joinable())
    {
        m_thread->join();
    }
    timer_delete(m_timerid);
}

void Scheduler::AddTask(std::shared_ptr<ISchedulerTask> task, 
                        std::chrono::milliseconds time_to_exec)
{
    auto new_task = std::make_shared<SchedulerTaskWrapper>
                    (task, std::chrono::steady_clock::now() + time_to_exec);
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_tasks.Push(new_task);
        m_is_earlier_task = true;
    }
    m_cvar.notify_one();
}

static void SetItimerspec (std::chrono::steady_clock::time_point time_point, 
                           struct itimerspec& delay)
{
    auto now = std::chrono::steady_clock::now();
    auto duration = time_point - now;

    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>
                 (duration).count();

    if (nanos <= 0) // FIX 2
    {
        nanos = 1;
    }
    
    delay.it_value.tv_sec = (nanos / 1000000000);
    delay.it_value.tv_nsec = nanos % 1000000000;

    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_nsec = 0;
}

}