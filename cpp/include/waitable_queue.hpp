/**********************
* waitable queue
* Author: Tal Frank
* Reviewer: Yael Novick
* Last update: 27/09/2026
**********************/

#ifndef ILRD_178_WAITABLE_QUEUE_HPP
#define ILRD_178_WAITABLE_QUEUE_HPP

#include <condition_variable>   // condition_variable
#include <mutex>                // mutex
#include <queue>       // queue

namespace ilrd_178
{
template< typename T, typename CONTAINER = std::queue<T> >
class WaitableQueue
{

public:
    explicit WaitableQueue();
    WaitableQueue(const WaitableQueue& other) = delete;
    WaitableQueue& operator= (const WaitableQueue& other) = delete;

    bool Pop(T& dest, std::chrono::milliseconds timeout);
    void Pop(T& dest);
    void Push(const T& element);

    bool IsEmpty() const ;

private:
    CONTAINER m_container;

    std::condition_variable m_cv;
    mutable std::mutex m_mutx;
};

template <typename T, typename CONTAINER>
WaitableQueue<T, CONTAINER>::WaitableQueue() {}

template <typename T, typename CONTAINER>
inline bool WaitableQueue<T, CONTAINER>::Pop(T &dest, std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lock(m_mutx);
    if (false == m_cv.wait_for(lock,
                               timeout,
                               [this] { return !m_container.empty(); }))
    {
        return false;
    }

    dest = m_container.front();
    m_container.pop();

    return true;
}

template <typename T, typename CONTAINER>
inline void WaitableQueue<T, CONTAINER>::Pop(T &dest)
{
    std::unique_lock<std::mutex> lock(m_mutx);
    m_cv.wait(lock, [this] { return !m_container.empty(); });

    dest = m_container.front();
    m_container.pop();
}

template <typename T, typename CONTAINER>
inline void WaitableQueue<T, CONTAINER>::Push(const T &element)
{
    std::lock_guard<std::mutex> lock(m_mutx);
    m_container.push(element);
    m_cv.notify_one();
}

template <typename T, typename CONTAINER>
inline bool WaitableQueue<T, CONTAINER>::IsEmpty() const
{
    return m_container.empty();
}

} // namespace ilrd_178

#endif // End of ILRD_178_WAITABLE_QUEUE_HPP