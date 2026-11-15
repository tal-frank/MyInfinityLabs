#include <string>
#include <array>
#include <iostream>

class UniqueCharFinder
{
public:
    static char findFirstUnique(const std::string& str);

};


char UniqueCharFinder::findFirstUnique(const std::string& str)
{
    std::array<int, 256> arr = {};
    for(unsigned char ch : str)
    {
        arr[ch] += 1;
    }

    for(unsigned char ch : str)
    {
        if (1 == arr[ch])
        {       
            return ch;
        }
    }
    return '\0';
}

int main()
{
    std::string str1("swiss");
    std::string str2("aabbcd");
    std::string str3("aabbcc");
    std::string str4("leetcode");
    
    std::cout << "Input: swiss\nOutput: ";
    std::cout << UniqueCharFinder::findFirstUnique(str1) << "\n";

    std::cout << "Input: aabbcd\nOutput: ";
    std::cout << UniqueCharFinder::findFirstUnique(str2) << "\n";

    std::cout << "Input: aabbcc\nOutput: ";
    std::cout << UniqueCharFinder::findFirstUnique(str3) << "\n";

    std::cout << "Input: leetcode\nOutput: ";
    std::cout << UniqueCharFinder::findFirstUnique(str4) << "\n";

    return 0;
}
