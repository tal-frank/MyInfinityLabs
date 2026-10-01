#include "thread_pool.hpp"

namespace ilrd_178
{
//-----------------------------------------------------------------------------------------//
//############################### THREAD POOL FUNCTIONS ###################################//
//-----------------------------------------------------------------------------------------//

ThreadPool::ThreadPool(size_t n_threads) : m_wpq(), m_threads(n_threads)
{
    // m_threads.reserve(n_threads);
    // for (size_t i = 0; i < n_threads; ++i)
    // {
    //     m_threads.emplace_back(&m_wpq);
    //     std::cout << "threadpool Ctor" << std::endl;
    // }
    for(WorkerThread& wt : m_threads)
    {
        wt.m_wpq = &m_wpq;
        wt.m_thread = std::thread(&WorkerThread::Run, &wt);
    }
}

void ThreadPool::AddTask(TASK_PTR task, Priority priority)
{
    TASK_PRIORITY_PTR TP(new TaskPriority(task, priority));
    m_wpq.Push(TP);
}

ThreadPool::~ThreadPool() 
    {
        for(WorkerThread& wt : m_threads)
        {
            wt.is_running = false;
        }

        std::shared_ptr<ThreadPool::Task> task(new ThreadPool::FunctionTask(JustForDebug));
        for(size_t i = 0; i < m_threads.size(); ++i)
        {
            AddTask(task, HIGH);
        }
    }

//-------------------------------------------------------------------------------------------//
//############################### WORKER THREAD FUNCTIONS ###################################//
//-------------------------------------------------------------------------------------------//

ThreadPool::WorkerThread::WorkerThread(WPQ* m_wpq) : is_running(true),
                                                     m_wpq(m_wpq) {}

void ThreadPool::WorkerThread::Run()
{
    while(is_running)
    {
        TASK_PRIORITY_PTR TP(NULL);
        m_wpq->Pop(TP);
        if (!is_running)
        {
            break;
        }

        if(NULL != TP && NULL != TP->m_ptask)
        {
            try
            {
                TP->m_ptask->Run();
            }
            catch(...) {}
        }
    }
}

ThreadPool::WorkerThread::~WorkerThread()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

//-------------------------------------------------------------------------------------------//
//############################### FUNCTION TASK FUNCTIONS ###################################//
//-------------------------------------------------------------------------------------------//

ThreadPool::FunctionTask::
FunctionTask(const std::function<void(void)> &func) 
            : m_func(func) {}


void ThreadPool::FunctionTask::Run()
{
    m_func();
}

//-------------------------------------------------------------------------------------------//
//############################### TASK PRIORITY FUNCTIONS ###################################//
//-------------------------------------------------------------------------------------------//

ThreadPool::TaskPriority::
TaskPriority(TASK_PTR task, ThreadPool::Priority priority) : m_ptask(task), m_priority(priority) {}

}