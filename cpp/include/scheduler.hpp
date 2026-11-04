#ifndef SCHEDULER_CPP
#define SCHEDULER_CPP

#include <memory> // shared_ptr
#include <chrono> // milliseconds

#include "singleton.hpp"
#include "waitable_queue.hpp"
#include "priority_queue.hpp"

namespace ilrd_178
{

class Scheduler
{
public:
    class ISchedulerTask
    {
    public:
        inline virtual ~ISchedulerTask() = default;
        virtual void Execute() = 0;
    };

    void AddTask(std::shared_ptr<ISchedulerTask> task, 
                 std::chrono::milliseconds time_to_exec);
    
    friend class Singleton<Scheduler>;

private:
    Scheduler(); 
    ~Scheduler();

    struct SchedulerTaskWrapper
    {
        SchedulerTaskWrapper(std::shared_ptr<ISchedulerTask> task,
                            std::chrono::steady_clock::time_point time)
                                                             : m_schedTask(task) ,
                                                               m_exec_time_ms(time) {}

        std::shared_ptr<ISchedulerTask> m_schedTask;
        std::chrono::steady_clock::time_point m_exec_time_ms;
    };

    class CompareTasks
    {
    public:
        inline bool operator() (const std::shared_ptr<SchedulerTaskWrapper>& task_lhs,
                                const std::shared_ptr<SchedulerTaskWrapper>& task_rhs)
        {
            return task_lhs->m_exec_time_ms > task_rhs->m_exec_time_ms;
        }
    };

    class PoisonPill: public ISchedulerTask
    {
        public:
        void Execute() override { }
    };

    bool m_invoke;
    bool m_is_running;
    bool m_is_earlier_task;

    timer_t m_timerid;
    std::shared_ptr<SchedulerTaskWrapper> m_curr_task;

    std::mutex m_mutex;
    std::condition_variable m_cvar;
    std::unique_ptr<std::thread> m_thread;

    WaitableQueue<std::shared_ptr<SchedulerTaskWrapper>, 
                  PriorityQueue<std::shared_ptr<SchedulerTaskWrapper>, 
                                std::vector<std::shared_ptr<SchedulerTaskWrapper>>, 
                                typename Scheduler::CompareTasks>> m_tasks;
};

}

#endif