#include <pthread.h>

class LockHolder
{
public:
    LockHolder(pthread_mutex_t& mutex);
    ~LockHolder();
private:
    LockHolder(const LockHolder& other_);
    LockHolder operator=(const LockHolder& other_);
    pthread_mutex_t& m_mutex;
};

LockHolder::LockHolder(pthread_mutex_t& mutex) : m_mutex(mutex)
{
    pthread_mutex_lock(&m_mutex);
}

LockHolder::~LockHolder()
{
    pthread_mutex_unlock(&m_mutex);
}
