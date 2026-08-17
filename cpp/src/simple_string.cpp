#include <cstring> // strcpy
#include <iostream> // std
#include <cstddef> // size_t

#include "simple_string.hpp"


namespace ilrd_178
{
    static char* CopyToNew(const char* src);

    String::String (const char* string)
    {
        m_cstr = CopyToNew(string);
    }

    String::String (const String& other_)
    {
        m_cstr = CopyToNew(other_.Cstr());
    }

    String& String::operator=(const String& other_)
    {
        if (this == &other_)
        {
            return *this;
        }

        delete[] m_cstr;
        m_cstr = CopyToNew(other_.Cstr());

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

    static char* CopyToNew(const char* src)
    {
        char* dest = new char[strlen(src) + 1];  
        strcpy(dest, src);
        return dest;
    }
}