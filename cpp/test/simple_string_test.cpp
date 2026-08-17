#include <iostream>

#include "simple_string.hpp"

using namespace ilrd_178;

void Foo(String s);
String Bla();

void Foo(String s)
{
    std::cout << s.Cstr() << std::endl;
}

String Bla()
{
    return "BlaBla";
}

int main()
{
    String s1("hello");
    String s3("world!");
    String s4("bla");
    std::cout << s1.Cstr() << " " << s3.Cstr() << std::endl;

    String s2(s3);
    std::cout << s2.Cstr() << std::endl;

    s3 = s1;
    std::cout << s3.Cstr() << std::endl;
    
    std::cout << "s1 length = " << s1.Length()
             << " s2 length = " << s2.Length() << std::endl;

    s3 = s3;
    std::cout << s3.Cstr() << std::endl;
    Foo("new string");

    std::cout << s4.Cstr() << std::endl;
    s4 = Bla();
    std::cout << s4.Cstr() << std::endl;
    return 0;
}