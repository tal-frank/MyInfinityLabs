#include <cstring> // strcpy
#include <iostream> // std
#include <cstddef> // size_t

#include "simple_string.hpp"

namespace ilrd_178
{
    String::String (const char* string)
    {
        //extract this, I wont mention it agagins
        m_cstr = new char[strlen(string) + 1];
        strcpy(m_cstr, string);
    }

    String::String (const String& other_)
    {
        m_cstr = new char[other_.Length() + 1];
        strcpy(m_cstr, other_.m_cstr);
    }

    String& String::operator=(const String& other_)
    {
        if (this == &other_)
        {
            return *this;
        }

        delete[] m_cstr;
        m_cstr = new char[other_.Length() + 1];
        
        strcpy(m_cstr, other_.m_cstr);

        return *this;
    }

    String::~String()
    {
        delete[] m_cstr;
    }

    size_t String::Length() const
    {
        return strlen(m_cstr);
    }

    const char* String::Cstr() const
    {
        return m_cstr;
    }
}