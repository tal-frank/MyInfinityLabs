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
    static char* CopyToNew(const char* src);
};
bool operator==(const String& str1, const String& str2);
bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
std::ostream& operator<<(std::ostream& os_, const String& str);
}

