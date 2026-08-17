#include <cstddef>
#include <cstring>

namespace ilrd_178
{ 
    class String 
    {
    public:
        String(const char*);
        String(const String& other_);
        String& operator=(const String& other_);
        ~String();
        size_t Length() const;
        const char* Cstr() const;
    private:
        char* m_cstr;
    };
}

