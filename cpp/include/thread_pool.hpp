/**********************
* thread pool
* Author: Tal Frank
* Reviewer: Roman Polugrudov
* Last update: 04/10/2026
**********************/

#ifndef ILRD_178_THREAD_POOL_HPP
#define ILRD_178_THREAD_POOL_HPP

#include <cstddef>     // size_t , NULL
#include <memory>      // shared_ptr
#include <functional>  // std::function
#include <vector>      // vector
#include <thread>      // threads
#include <atomic>      // atomic
#include <list>        // list
#include <future>      // future, promise
#include <semaphore.h> // semaphore


#include "waitable_queue.hpp"
#include "priority_queue.hpp"

namespace ilrd_178
{
inline void JustForDebug() {};

class ThreadPool
{
//------------------------------------------------------------------------------------//
//################################# DECLARATIONS #####################################//
//------------------------------------------------------------------------------------//

private:
    struct TaskPriority;
public:
    class Task;
    template<typename OUTPUT>
    class FutureTask;
    class FunctionTask;
    
    using TASK_PTR = std::shared_ptr<Task>;
    using TASK_PRIORITY_PTR = std::shared_ptr<TaskPriority>;
    
    
    enum Priority : int
    {
        HIGH = 1,
        NORMAL,
        LOW
    };

    ThreadPool(size_t nthreads = 0);
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool& other) = delete;

    ~ThreadPool();
    
    void Pause();
    void Resume();
    void SetNumOfThreads(size_t nthreads);
    void AddTask(TASK_PTR task, Priority priority);
    
//----------------------------------------------------------------------------------//
//################################# TASK CLASS #####################################//
//----------------------------------------------------------------------------------//

    class Task
    {
    public:
        explicit Task() {}
        virtual ~Task() {} // todo
        Task(const Task& other) = delete;
        Task& operator=(const Task& other) = delete;
        virtual void Run() = 0;

        class CmpFunc
        {
        public:
            bool operator()(const TASK_PRIORITY_PTR& task1, const TASK_PRIORITY_PTR& task2);
        };
    };

    using PQ = PriorityQueue<TASK_PRIORITY_PTR, std::vector<TASK_PRIORITY_PTR>, Task::CmpFunc>;
    using WPQ = WaitableQueue<TASK_PRIORITY_PTR, PQ>;


//-------------------------------------------------------------------------------------------//
//################################# FUNCTION TASK CLASS #####################################//
//-------------------------------------------------------------------------------------------//

    class FunctionTask : public Task
    {
    public:
        explicit FunctionTask(const std::function<void(void)>& func);
        void Run();
    private:
        std::function<void(void)> m_func;
    };
    
//-----------------------------------------------------------------------------------------//
//################################# FUTURE TASK CLASS #####################################//
//-----------------------------------------------------------------------------------------//

    template<typename OUTPUT>
    class FutureTask: public Task
    {
    public:
        explicit FutureTask(std::function<OUTPUT(void)>& func, 
                            OUTPUT& output);
        void Run();
        OUTPUT Get(); // todo (blocking function) //-> return m_output;
    private:
        sem_t sem_get_output;
        std::function<OUTPUT(void)> m_func; 
        OUTPUT& m_output;
    };


private:
    
//---------------------------------------------------------------------------------------//
//############################### WORKER THREAD CLASS ###################################//
//---------------------------------------------------------------------------------------//
    class WorkerThread
    {
        friend class ThreadPool;
    public:
        WorkerThread();
        WorkerThread(WPQ* m_wpq_ptr);

        ~WorkerThread();
        void Run();
        
    private:
        static thread_local WorkerThread* this_thread;
        
        std::atomic<bool> is_running;
        WPQ* m_wpq_ptr;
        std::thread m_thread;
    };

//---------------------------------------------------------------------------------------//
//############################### TASK PRIORITY CLASS ###################################//
//---------------------------------------------------------------------------------------//

    struct TaskPriority
    {
    public:
        TaskPriority(TASK_PTR task, Priority priority);

        TASK_PTR m_ptask;
        Priority m_priority;
    };

    static std::atomic<bool> is_paused;
    WPQ m_wpq;
    std::list<std::shared_ptr<WorkerThread> > m_threads;
};

//-----------------------------------------------------------------------------------------//
//############################### FUTURE TASK FUNCTIONS ###################################//
//-----------------------------------------------------------------------------------------//

template <typename OUTPUT>
ThreadPool::FutureTask<OUTPUT>::
FutureTask(std::function<OUTPUT(void)> &func, OUTPUT &output)
        : m_func(func), 
        m_output(output)
{
    sem_init(&sem_get_output, 0, 0);    
}

template <typename OUTPUT>
void ThreadPool::FutureTask<OUTPUT>::Run()
{
    m_output = m_func();
    sem_post(&sem_get_output);
}

template<typename OUTPUT>
OUTPUT ThreadPool::FutureTask<OUTPUT>::Get()
{
    sem_wait(&sem_get_output);
    sem_post(&sem_get_output);
    return m_output;
}


} // namespace ilrd_178

#endif // ILRD_178_THREAD_POOL_HPP