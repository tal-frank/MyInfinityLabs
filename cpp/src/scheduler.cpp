#include <thread>  // thread
#include <csignal>
#include <cstring> // memset

#include "scheduler.hpp"

namespace ilrd_178
{
static void SetItimerspec(std::chrono::milliseconds msec, struct itimerspec& delay);

Scheduler::Scheduler() : m_invoke(false), 
                         m_is_running(true), 
                         m_is_earlier_task(false), 
                         m_curr_task({}, std::chrono::milliseconds(0))
{
    struct sigevent sig_e;
    // SetSigEvent(this, sig_e);
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
                                    // m_invoke = false;
                                    m_tasks.Pop(m_curr_task);

                                    {
                                        std::unique_lock<std::mutex> lock(m_mutex);
                                        m_invoke = false;
                                        m_is_earlier_task = false;
                                        // std::lock_guard<std::mutex> lock(m_mutex_clock);
                                        struct itimerspec delay;
                                        SetItimerspec(m_curr_task->m_exec_time_ms, delay);
                                        timer_settime(m_timerid, 0, &delay, nullptr);
                                        m_cvar.wait(lock, [this] { return m_invoke ||
                                                                          m_is_earlier_task ||
                                                                          !m_is_running;});
                                    }
                                    
                                    // std::unique_lock<std::mutex> lock(m_mutex);
                                    // m_cvar.wait(lock, [this] { return m_invoke; });
                                    
                                    // if (m_is_earlier_task)
                                    if (std::chrono::steady_clock::now() < 
                                        m_curr_task->m_exec_time_ms)
                                    {
                                        // std::shared_ptr<SchedulerTaskWrapper> curr_task_ptr = 
                                            // std::make_shared<SchedulerTaskWrapper>(m_curr_task);
                                        m_tasks.Push(m_curr_task);
                                        continue;
                                        // m_tasks.Pop(m_curr_task);
                                        // m_is_earlier_task = false;
                                    }

                                    try
                                    {
                                        m_curr_task->m_schedTask->Execute();
                                    }
                                    catch(...) {}
                                    
                                    // if (m_is_running)
                                    // {
                                    //     m_curr_task->m_schedTask->Execute();
                                    // }
                                }
                            }));
}

Scheduler::~Scheduler()
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_is_running = false;
    }
    // std::shared_ptr<ISchedulerTask> end_task = {};
    m_cvar.notify_one();
    AddTask(nullptr, std::chrono::milliseconds(0));
    
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

// void Scheduler::AddTask(std::shared_ptr<ISchedulerTask> task, 
//                         std::chrono::milliseconds time_to_exec)
// {
//     auto now = std::chrono::system_clock::now();
//     auto duration = now.time_since_epoch();
//     std::chrono::milliseconds msec = 
//          std::chrono::duration_cast<std::chrono::milliseconds>(duration);
//     SchedulerTaskWrapper new_task(task, msec + time_to_exec);

//     std::shared_ptr<SchedulerTaskWrapper> new_task_ptr = 
//             std::make_shared<SchedulerTaskWrapper>(new_task);
//     m_tasks.Push(new_task_ptr);

//     struct itimerspec timer_state;
//     timer_gettime(m_timerid, &timer_state);
//     auto remaining_ms = std::chrono::seconds(timer_state.it_value.tv_sec) + 
//                         std::chrono::duration_cast<std::chrono::milliseconds>
//                         (std::chrono::nanoseconds(timer_state.it_value.tv_nsec));
//     // if (static_cast<std::chrono::seconds>(timer_state.it_value.tv_sec) + 
//     //     static_cast<std::chrono::milliseconds>(timer_state.it_value.tv_nsec) < 
//     //     time_to_exec)
//     if (remaining_ms < time_to_exec)
//     {
//         std::lock_guard<std::mutex> lock(m_mutex_clock);
//         struct itimerspec delay;
//         SetItimerspec(time_to_exec, delay);
//         timer_settime(m_timerid, 0, &delay, nullptr);
//         m_is_earlier_task = true;
//     }
// }

static void SetItimerspec (std::chrono::steady_clock::time_point time_point, 
                           struct itimerspec& delay)
{
    auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>
                      (time_point.time_since_epoch()).count();

    delay.it_value.tv_sec = nanos / 1000000000;
    delay.it_value.tv_nsec = nanos % 1000000000;

    delay.it_interval.tv_sec = 0;
    delay.it_interval.tv_nsec = 0;
}

// static void SetItimerspec (std::chrono::milliseconds msec, struct itimerspec& delay)
// {
//     struct timespec tspec;
//     clock_gettime(CLOCK_REALTIME, &tspec);

//     auto secs = std::chrono::duration_cast<std::chrono::seconds>(msec);
//     auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(msec - secs);

//     delay.it_value.tv_sec = secs.count() - tspec.tv_sec;
//     delay.it_value.tv_nsec = nanos.count() - tspec.tv_nsec;

//     delay.it_interval.tv_sec = 0;
//     delay.it_interval.tv_nsec = 0;
// }

// static void SetSigEvent (Scheduler* sched, struct sigevent& sig_e)
// {
//     std::memset(&sig_e, 0, sizeof(struct sigevent));
//     sig_e.sigev_notify = SIGEV_THREAD;
//     sig_e.sigev_value.sival_ptr = sched;
//     sig_e.sigev_notify_function = [] (union sigval sv) 
//                                 {
//                                     auto scheduler = static_cast<Scheduler*>(sv.sival_ptr);
//                                     scheduler->m_invoke = true;
//                                 };
// }

}