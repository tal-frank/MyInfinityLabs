/**********************
* singleton
* Author: Tal Frank
* Reviewer: 
* Last update: 08/10/2026
**********************/

#ifndef __ILRD__SINGLETON__HPP__
#define __ILRD__SINGLETON__HPP__

#include <mutex>   // mutex
#include <atomic>  // atomic variable
#include <cstdlib> // atexit, abort

namespace ilrd_178
{
template <typename T>
class Singleton
{
public:
    static T* GetInstance();

    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;

private:
    Singleton();
    static void CleanUp();

    static std::mutex s_mutex;
    static std::atomic<T*> s_instance;
    static bool s_is_destroyed;
};

template <typename T>
std::mutex Singleton<T>::s_mutex;

template <typename T>
std::atomic<T*> Singleton<T>::s_instance(nullptr);

template <typename T>
bool Singleton<T>::s_is_destroyed = false;

template <typename T>
Singleton<T>::Singleton() {}

template <typename T>
inline void Singleton<T>::CleanUp()
{
    delete s_instance;
    s_instance = nullptr;
    s_is_destroyed = true;
}

template <typename T>
inline T* Singleton<T>::GetInstance()
{
    if (nullptr == s_instance)
    {
        std::lock_guard<std::mutex> lock(s_mutex); 
        if (nullptr == s_instance)
        {
            if (Singleton::s_is_destroyed)
            {
                std::abort();
            }
            s_instance.store(new T, std::memory_order_release);
            std::atexit(CleanUp);
        }
    }
    return s_instance;
}

}

#endif