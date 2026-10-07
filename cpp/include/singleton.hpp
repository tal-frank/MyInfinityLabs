/**********************
* singleton
* Author: Tal Frank
* Reviewer: 
* Last update: 08/10/2026
**********************/

#include <mutex>

#ifndef __ILRD__SINGLETON__HPP__
#define __ILRD__SINGLETON__HPP__


namespace ilrd_178
{

template <typename T>
class Singleton
{
public:
    static Singleton GetInstance();

private:
    Singleton();

    std::mutex;
    static Singleton instance;
};

}

#endif