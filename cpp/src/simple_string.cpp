/**********************
* simple string
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 17/08/2026
**********************/

#include <cstring> // strcpy
#include <iostream> // std
#include <cstddef> // size_t

#include "simple_string.hpp"


namespace ilrd_178
{
String::String (const char* string) : m_cstr(CopyToNew(string)) {}

String::String (const String& other_) : m_cstr(CopyToNew(other_.Cstr())) {}

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
    m_cstr = NULL;
}

size_t String::Length() const
{
    return strlen(m_cstr);
}

const char* String::Cstr() const
{
    return m_cstr;
}

char* String::CopyToNew(const char* src)
{
    size_t len = strlen(src) + 1;
    char* dest = new char[len];
    memcpy(dest, src, len);
    return dest;
}

bool operator==(const String& str1, const String& str2)
{
    return 0 == strcmp(str1.Cstr(), str2.Cstr());
}

bool operator<(const String& str1, const String& str2)
{
    return 0 > strcmp(str1.Cstr(), str2.Cstr());
}

bool operator>(const String& str1, const String& str2)
{
    return 0 < strcmp(str1.Cstr(), str2.Cstr());
}

std::ostream& operator<<(std::ostream& os_, const String& str)
{
    return os_<< str.Cstr();
}
}
