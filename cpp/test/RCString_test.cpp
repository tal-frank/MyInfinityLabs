const char* RED = "\033[1;31m";
const char* GREEN = "\033[1;32m";
const char* YELLOW = "\033[1;33m";
const char* BLUE = "\033[1;34m";
const char* RESET = "\033[0m";

#include <iostream>

#include "RCString.hpp"

using namespace ilrd178;

int main()
{
    char* str = new char[100];
    strcpy(str, "are you copying me??");
    char* s_1 = "another copy";
    char* s_2 = "bnother copy";

    RCString str1;
    RCString str2(str);
    RCString str3(str2);
    RCString str4;
    RCString str5(s_1);
    RCString str6(str5);
    str4 = str3;

//-------------------------------------------------------------------------------------//
//################################# CREATING TEST #####################################//
//-------------------------------------------------------------------------------------//

    std::cout << BLUE << "\nCREATING TEST" << RESET << std::endl;

    std::cout << "str1 = " << str1.ToCStr() << std::endl;
    std::cout << "str2 = " << str2.ToCStr() << std::endl;
    std::cout << "str3 = " << str3.ToCStr() << std::endl;

    (str1.ToCStr()) == (str2.ToCStr()) ? 
            std::cout << RED << "creating wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "creating right\n---SUCCESS---\n" << RESET << std::endl;

    (str2.ToCStr()) != (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;

    (str4.ToCStr()) != (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;


//------------------------------------------------------------------------------------//
//################################# READING TEST #####################################//
//------------------------------------------------------------------------------------// 
    char ch = str2[2];

    std::cout << BLUE << "READING TEST" << RESET << std::endl;

    std::cout << "str2[2] = " << ch << std::endl;
    'e' != ch ? std::cout << RED << "reading wrong\n---SUCCESS---\n" << RESET << std::endl :
                std::cout << GREEN << "reading right\n---FAILURE---\n" << RESET << std::endl;
    
    (str2.ToCStr()) != (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;
    
//------------------------------------------------------------------------------------//
//################################# WRITING TEST #####################################//
//------------------------------------------------------------------------------------//
    
    str2[1] = ch; 

    std::cout << BLUE << "WRITING TEST" << RESET << std::endl;

    std::cout << "str2[1] = " << str2[1] << std::endl;
    std::cout << "str2 = " << str2.ToCStr() << std::endl;
    std::cout << "str3 = " << str3.ToCStr() << std::endl;

    'e' != str2[1] ? std::cout << RED << " and writing\n---FAILURE---\n" << RESET << std::endl :
                     std::cout << GREEN << "reading without writing\n---SUCCESS---\n" << RESET << std::endl;

    (str2.ToCStr()) == (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;

//---------------------------------------------------------------------------------------//
//################################# ASSIGNMENT TEST #####################################//
//---------------------------------------------------------------------------------------//

    str6 = str3;

    std::cout << BLUE << "ASSIGNMENT TEST" << RESET << std::endl;

    std::cout << "str4 = " << str4.ToCStr() << std::endl;
    std::cout << "str5 = " << str5.ToCStr() << std::endl;
    std::cout << "str6 = " << str6.ToCStr() << std::endl;

    (str5.ToCStr()) == (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;

    (str6.ToCStr()) != (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;
            
    str5 = str3;
    std::cout << "str5 = " << str5.ToCStr() << std::endl;
    (str5.ToCStr()) != (str3.ToCStr()) ? 
            std::cout << RED << "copying wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "copying right\n---SUCCESS---\n" << RESET << std::endl;

//-----------------------------------------------------------------------------------//
//################################# EQUALITY TEST #####################################//
//-----------------------------------------------------------------------------------// 

    RCString str7(s_1);
    RCString str8(s_1);
    RCString str9(s_2);

    std::cout << BLUE << "EQUALITY TEST" << RESET << std::endl;

    0 == (str7 == str8) ? 
            std::cout << RED << "equality is wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "equality is right\n---SUCCESS---\n" << RESET << std::endl;

    0 == (str7 != str9) ? 
            std::cout << RED << "equality is wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "equality is right\n---SUCCESS---\n" << RESET << std::endl;
    
    0 == (str8 < str9) ? 
            std::cout << RED << "equality is wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "equality is right\n---SUCCESS---\n" << RESET << std::endl;

    0 == (str9 > str8) ? 
            std::cout << RED << "equality is wrong\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "equality is right\n---SUCCESS---\n" << RESET << std::endl;

//-----------------------------------------------------------------------------------//
//################################# LENGTH TEST #####################################//
//-----------------------------------------------------------------------------------// 

    std::cout << BLUE << "LENGTH TEST" << RESET << std::endl;
    std::cout << "sring length is : "<< str2.Length() << std::endl;
    20 != str2.Length() ? 
            std::cout << RED << "wrong length\n---FAILURE---\n" << RESET << std::endl :
            std::cout << GREEN << "right length\n---SUCCESS---\n" << RESET << std::endl;

    delete[] str;
    
    //-----------------------------------------------------------------------------------//
    //################################# LENGTH TEST #####################################//
    //-----------------------------------------------------------------------------------// 
    
    const RCString str10(str2);
    ch = str10[4];
    std::cout << "str10 = " << str10.ToCStr() << std::endl;
    std::cout << "ch = " << ch << std::endl;
    std::cout << "length = " << str10.Length() << std::endl;

    return 0;
}