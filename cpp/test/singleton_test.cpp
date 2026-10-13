const char* RED = "\033[1;31m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* BLUE = "\033[1;34m";
const char* RESET = "\033[0m";

#include <iostream>

#include "singleton.hpp"

using namespace ilrd_178;

int main()
{
    int* singleton1 = Singleton<int>::GetInstance();
    if (nullptr == singleton1)
    {
        std::cout << RED << "FAILURE:" << RESET << std::endl;
        std::cout << RED << "an error occured allocating a singlton first time" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "PASSED:" << RESET << std::endl;
        std::cout << GREEN << "a singleton has been initiated" << RESET << std::endl;
    }
    
    int* singleton2 = Singleton<int>::GetInstance();
    if (singleton1 != singleton2)
    {
        std::cout << RED << "FAILURE:" << RESET << std::endl;
        std::cout << RED << "was able to allocate another singleton" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "PASSED:" << RESET << std::endl;
        std::cout << GREEN << "a second singleton initilization is blocked" << RESET << std::endl;
    }

}