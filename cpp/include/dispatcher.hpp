/**********************
* dispatcher
* Author: Tal Frank
* Reviewer: Almog Nimni
* Last update: 18/10/2026
**********************/

#ifndef ILRD_178_DISPATCHER_Callback_HPP
#define ILRD_178_DISPATCHER_Callback_HPP

#include <vector>    // vector
#include <algorithm> // find

namespace ilrd_178
{

//-------------------------------------------------------------------------------//
//################################# CLASSES #####################################//
//-------------------------------------------------------------------------------//

template<typename T>
class Dispatcher;

//------------------------ CallbackBase ------------------------//

template<typename T>
class CallbackBase
{
public:
    CallbackBase();
    virtual ~CallbackBase() = 0;
    virtual void Callback(const T& message) = 0;
    virtual void Stop() = 0;

private:
    friend class Dispatcher<T>;

    Dispatcher<T>* m_dispatcher;
};

//------------------------ Callback ------------------------//

template<typename SUBSCRIBER, typename T>
class CallBack : public CallbackBase<T>
{
public:
    using ActionFunc = void (SUBSCRIBER::*)(const T&);
    using StopFunc   = void (SUBSCRIBER::*)();

    CallBack(SUBSCRIBER& subscriber, ActionFunc action, StopFunc stop = nullptr);
    ~CallBack();

    CallBack(const CallBack&) = delete;
    CallBack& operator=(const CallBack&) = delete;

    void Callback(const T& message) override;
    void Stop() override;

private:
    SUBSCRIBER& m_subscriber;
    ActionFunc  m_action;
    StopFunc    m_stop;
};

//------------------------ dispatcher ------------------------//

template<typename T>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher();

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    void Subscribe(CallbackBase<T>* Callback);
    void Unsubscribe(CallbackBase<T>* Callback);
    void NotifyAll(const T& message);

private:
    std::vector<CallbackBase<T>*> m_subscribers;
};

//----------------------------------------------------------------------------------------------//
//################################# CALLBACKBASE FUNCTIONS #####################################//
//----------------------------------------------------------------------------------------------//

template <typename T>
inline CallbackBase<T>::CallbackBase() : m_dispatcher(nullptr) {}

template <typename T>
CallbackBase<T>::~CallbackBase()
{
    if (nullptr != m_dispatcher)
    {
        m_dispatcher->Unsubscribe(this);
    }
}

//------------------------------------------------------------------------------------------//
//################################# CALLBACK FUNCTIONS #####################################//
//------------------------------------------------------------------------------------------//

template <typename SUBSCRIBER, typename T>
inline CallBack<SUBSCRIBER, T>::CallBack(SUBSCRIBER &subscriber, ActionFunc action, StopFunc stop)
                               : m_subscriber(subscriber), 
                                 m_action(action), 
                                 m_stop(stop) {}

template <typename SUBSCRIBER, typename T>
CallBack<SUBSCRIBER, T>::~CallBack() {}

template <typename SUBSCRIBER, typename T>
void CallBack<SUBSCRIBER, T>::Callback(const T &message)
{
    (m_subscriber.*m_action)(message);
}

template <typename SUBSCRIBER, typename T>
inline void CallBack<SUBSCRIBER, T>::Stop()
{
    if (nullptr != m_stop)
    {
        (m_subscriber.*m_stop)();
    }
}

//--------------------------------------------------------------------------------------------//
//################################# DISPATCHER FUNCTIONS #####################################//
//--------------------------------------------------------------------------------------------//

template <typename T>
Dispatcher<T>::~Dispatcher()
{
    std::vector<CallbackBase<T>*> subs = m_subscribers;
    m_subscribers.clear();
    for (CallbackBase<T>* subscriber : subs)
    {
        if (nullptr != subscriber)
        {
            subscriber->m_dispatcher = nullptr;
            subscriber->Stop();
        }
    }
}

template <typename T>
void Dispatcher<T>::Subscribe(CallbackBase<T> *Callback)
{
    if (nullptr != Callback)
    {
        Callback->m_dispatcher = this;
        m_subscribers.push_back(Callback);
    }
}

template <typename T>
void Dispatcher<T>::Unsubscribe(CallbackBase<T> *Callback)
{
    auto iter = std::find(m_subscribers.begin(), m_subscribers.end(), Callback);
    if (iter != m_subscribers.end())
    {
        (*iter)->m_dispatcher = nullptr;
        m_subscribers.erase(iter);
    }
}

template <typename T>
void Dispatcher<T>::NotifyAll(const T &message)
{
    std::vector<CallbackBase<T>*> subs = m_subscribers;
    for (CallbackBase<T>* subscriber : subs)
    {
        auto iter = std::find(m_subscribers.begin(), m_subscribers.end(), subscriber);
        if (iter != m_subscribers.end() && nullptr != subscriber)
        {
            subscriber->Callback(message);
        }
    }
}



} // namespace ilrd_178

#endif // End of ILRD_178_DISPATCHER_Callback_HPP