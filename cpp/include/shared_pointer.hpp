#ifndef __SHARED_POINTER__
#define __SHARED_POINTER__

#include <pthread.h>

#include <cstddef> // size_t

namespace ilrd178
{
//------------------------------------------------------------------------------//
//################################# STRUCT #####################################//
//------------------------------------------------------------------------------//

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr); 
    inline SharedPtr(const SharedPtr& other_); 
    inline SharedPtr& operator=(const SharedPtr& other_); 
    
    template <typename U>
    SharedPtr(const SharedPtr<U>& other_);
   
    template<typename U>
    SharedPtr& operator=(const SharedPtr<U>& other_);
    
    ~SharedPtr();

    T& operator*();
    T* operator->();

private:    
    T* m_data;
    size_t* m_ref_cnt;

    SharedPtr();
    template <typename U>
    friend class SharedPtr;
};

//---------------------------------------------------------------------------------------//
//################################# STRUCT FUNCTION #####################################//
//---------------------------------------------------------------------------------------//

template <typename T>
inline SharedPtr<T>::SharedPtr(T* ptr) : m_data(ptr), m_ref_cnt(new size_t)
{
    *m_ref_cnt = 1;
}

template <typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& other_) : m_data(other_.m_data), 
                                                          m_ref_cnt(other_.m_ref_cnt)
{
    *m_ref_cnt += 1;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr &other_)
{
    if (this != &other_)
    {
        if (1 > --(*m_ref_cnt))
        {
            delete m_data;
            m_data = NULL;
            delete m_ref_cnt;
            m_ref_cnt = NULL;
        }
        m_data = other_.m_data;
        m_ref_cnt = other_.m_ref_cnt;
        *m_ref_cnt += 1;
    }
    return *this;
}

template <typename T>
SharedPtr<T>::~SharedPtr() 
{
    if (1 > --(*m_ref_cnt))
    {
        delete m_data;
        m_data = NULL;
        delete m_ref_cnt;
        m_ref_cnt = NULL;
    }
}

template <typename T>
inline T& SharedPtr<T>::operator*()
{
    return *m_data;
}

template <typename T>
inline T* SharedPtr<T>::operator->()
{
    return m_data;
}

template <typename T>
template <typename U>
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other_) : m_data(other_.m_data),
                                                      m_ref_cnt(other_.m_ref_cnt)
{
    *m_ref_cnt += 1;
}

template <typename T>
template <typename U>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<U>& other_)
{
    if (this->m_data != other_.m_data)
    {
        if (1 > --(*m_ref_cnt))
        {
            delete m_data;
            m_data = NULL;
            delete m_ref_cnt;
            m_ref_cnt = NULL;
        }
        m_data = other_.m_data;
        m_ref_cnt = other_.m_ref_cnt;
        *m_ref_cnt += 1;
    }
    return *this;
}

}

#endif