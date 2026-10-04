#include "thread_pool.hpp"

#include <iostream>
namespace ilrd_178
{

void PauseAllThreads(void);
void ResumeAllThreads(void);

thread_local ThreadPool::WorkerThread* ThreadPool::WorkerThread::this_thread = NULL;
std::atomic<bool> ThreadPool::is_paused(false);

sem_t sem_pause = {0};
sem_t sem_thread_erase = {0};

//-----------------------------------------------------------------------------------------//
//############################### THREAD POOL FUNCTIONS ###################################//
//-----------------------------------------------------------------------------------------//

ThreadPool::ThreadPool(size_t n_threads) : m_wpq()
{
    if (0 == n_threads)
    {
        size_t hc_result = std::thread::hardware_concurrency();
        n_threads = hc_result ? hc_result : 1;
    }

    sem_init(&sem_pause, 0, 0);
    for (size_t i = 0; i < n_threads; ++i)
    {
        m_threads.emplace_back(std::make_shared<WorkerThread>(&m_wpq));
    }
}

ThreadPool::~ThreadPool() 
{
    TASK_PTR task(new ThreadPool::FunctionTask(
                     [this] ()
                    {
                        WorkerThread::this_thread->is_running = false;
                    }));

    for(auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
    {
        AddTask(task, static_cast<Priority>(LOW + 1));
    }
    m_threads.clear();
}

void ThreadPool::AddTask(TASK_PTR task, Priority priority)
{
    TASK_PRIORITY_PTR TP(new TaskPriority(task, priority));
    m_wpq.Push(TP);
}

void ThreadPool::Pause()
{
    if (false == ThreadPool::is_paused)
    {
        ThreadPool::is_paused = true;
        for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
        {
            TASK_PTR task(new ThreadPool::FunctionTask(PauseAllThreads));
            AddTask(task, HIGH);
        }
    }
}

void ThreadPool::Resume()
{
    if (true == ThreadPool::is_paused)
    {
        for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
        {
            sem_post(&sem_pause);
        }
        ThreadPool::is_paused = false;
    }
}

void ThreadPool::SetNumOfThreads(size_t nthreads)
{
    if (nthreads < m_threads.size())
    {
        TASK_PTR task(new ThreadPool::FunctionTask(
                     [this] ()
                    {
                        WorkerThread::this_thread->is_running = false;
                        sem_post(&sem_thread_erase);
                    }));

        for (size_t i = nthreads; i < m_threads.size(); ++i)
        {
            AddTask(task, HIGH);
        }
        for (size_t i = nthreads; i < m_threads.size(); ++i)
        {
            sem_wait(&sem_thread_erase);
        }

        for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter)
        {
            if (false == (*iter)->is_running)
            {
                iter = m_threads.erase(iter);
            }
        }
    }
    else
    {
        for (size_t i = m_threads.size(); i < nthreads; ++i)
        {
            m_threads.emplace_back(std::make_shared<WorkerThread>(&m_wpq));
        }
    }
}

void PauseAllThreads(void)
{
    sem_wait(&sem_pause);
}

void ResumeAllThreads(void)
{
    sem_post(&sem_pause);
}

//-------------------------------------------------------------------------------------------//
//############################### WORKER THREAD FUNCTIONS ###################################//
//-------------------------------------------------------------------------------------------//

ThreadPool::WorkerThread::WorkerThread() : is_running(true) {}

ThreadPool::WorkerThread::WorkerThread(WPQ* m_wpq_ptr) : is_running(true),
                                                         m_wpq_ptr(m_wpq_ptr),
                                                         m_thread(std::thread(&WorkerThread::Run, this)) {}

void ThreadPool::WorkerThread::Run()
{
    this_thread = this;
    while(is_running)
    {
        TASK_PRIORITY_PTR TP(NULL);
        m_wpq_ptr->Pop(TP);
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

bool ThreadPool::Task::
CmpFunc::operator()(const TASK_PRIORITY_PTR &task1, const TASK_PRIORITY_PTR &task2)
{
    return (task1->m_priority > task2->m_priority);
}

}