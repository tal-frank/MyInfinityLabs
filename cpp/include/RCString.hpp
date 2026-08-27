/**********************
* reference counting string
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 27/08/2026
**********************/

#include <cstring> // memcpy
#include <cstddef> // size_t
#include <new> // bad_alloc
#include <iostream> // bad_alloc

namespace ilrd178
{
static const int first_ref = 1;

//-----------------------------------------------------------------------------------//
//################################# DATA STRUCT #####################################//
//-----------------------------------------------------------------------------------//

class RCString_Data
{
public:
    inline RCString_Data(const char* str = "");
    inline ~RCString_Data();

    inline size_t GetRefCnt();
    inline char* GetStr();

    inline void SetRefCnt(size_t cnt);
    inline char& SetStr(size_t index);

    inline char* InitRCString(const char* src);

private:
    char* m_str;
    size_t m_ref_cnt;
};

//-------------------------------------------------------------------------------------//
//################################# STRING STRUCT #####################################//
//-------------------------------------------------------------------------------------//

class RCString
{
public:
    inline RCString(const char* s_ = "");
    inline RCString(const RCString& other_);
    inline ~RCString();

    inline RCString& operator=(const RCString& other_);
    inline char& operator[](size_t index) const;
    inline char& operator[](size_t index);

    inline size_t Length();
    inline char* ToCStr() const;
    
private:
    RCString_Data* m_data;
};

//------------------------------------------------------------------------------------//
//################################# CONSTRUCTORS #####################################//
//------------------------------------------------------------------------------------//

inline RCString::RCString(const char* s_) : m_data(new RCString_Data(s_)) {}

inline RCString::RCString(const RCString& other_) : m_data(other_.m_data)
{
    m_data->SetRefCnt(m_data->GetRefCnt() + 1);
}

inline RCString_Data::RCString_Data(const char* str) : 
                      m_str(InitRCString(str)), m_ref_cnt(first_ref) {}

//---------------------------------------------------------------------------------------//
//################################# SETERS & GETERS #####################################//
//---------------------------------------------------------------------------------------//

inline char* RCString::ToCStr() const
{
    return this->m_data->GetStr();
}

inline void RCString_Data::SetRefCnt(size_t cnt)
{
    m_ref_cnt = cnt;
}

inline size_t RCString_Data::GetRefCnt()
{
    return m_ref_cnt;
}

inline char* RCString_Data::GetStr()
{
    return m_str;
}

inline char& RCString_Data::SetStr(size_t index)
{
    return m_str[index];
}

//-----------------------------------------------------------------------------------//
//################################# DESTRUCTORS #####################################//
//-----------------------------------------------------------------------------------//

inline RCString::~RCString() 
{
    m_data->SetRefCnt(m_data->GetRefCnt() - 1);
    if (0 == m_data->GetRefCnt())
    {
        delete this->m_data;
        this->m_data = NULL;
    }
}

inline RCString_Data::~RCString_Data()
{
    delete[] m_str;
}

//---------------------------------------------------------------------------------//
//################################# OPERATORS #####################################//
//---------------------------------------------------------------------------------//

inline RCString& RCString::operator=(const RCString& other_)
{
    if (other_.m_data != this->m_data)
    {
        this->m_data->SetRefCnt(m_data->GetRefCnt() - 1);
        if (first_ref > this->m_data->GetRefCnt())
        {
            delete this->m_data;
        }

        this->m_data = other_.m_data;
        m_data->SetRefCnt(m_data->GetRefCnt() + 1);
    }

    return *this;
}

inline int operator==(const RCString& str1, const RCString str2)
{
    return !!strcmp(str1.ToCStr(), str2.ToCStr());
}

inline int operator!=(const RCString& str1, const RCString str2)
{
    return !strcmp(str1.ToCStr(), str2.ToCStr());
}

inline int operator<(const RCString& str1, const RCString str2)
{
    return 0 < strcmp(str1.ToCStr(), str2.ToCStr());
}

inline int operator>(const RCString& str1, const RCString str2)
{
    return 0 > strcmp(str1.ToCStr(), str2.ToCStr());
}

inline char& RCString::operator[](size_t index) const
{
    return this->ToCStr()[index];
}

inline char& RCString::operator[](size_t index)
{
    if (first_ref < this->m_data->GetRefCnt())
    {
        this->m_data->SetRefCnt(this->m_data->GetRefCnt() - 1);

        RCString_Data* new_data = new RCString_Data(this->m_data->GetStr());
        this->m_data = new_data;
    }
    return this->m_data->SetStr(index);
}

inline char* RCString_Data::InitRCString(const char* src)
{
    size_t len = strlen(src) + 1;
    try
    {
        char* dest = new char[len];
        memcpy(dest, src, len);
        return dest;
    }
    catch (const std::bad_alloc& ba)
    {
        std::cerr << "allocation failure : " <<ba.what() << std::endl;
        return NULL;
    }
}

inline size_t RCString::Length()
{
    return strlen(this->ToCStr());
}

}