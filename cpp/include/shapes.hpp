/**********************
* shapes
* Author: Tal Frank
* Reviewer: Ori Joseph
* Last update: 02/09/2026
**********************/

#ifndef ILRD178_SHAPES_HPP
#define ILRD178_SHAPES_HPP

#include <iostream> 
#include <string>

//------------------------------------------------------------//
//************************ BASE CLASS ************************//
//------------------------------------------------------------//

class shape
{
public:
    inline shape();
    inline shape(const std::string shape_name);
    virtual ~shape() = 0;

    inline void Draw();   
    inline void Move(int offset);

private:
    std::string shape_name;
    int offset;
};

//----------------------------------------------------------------//
//************************ SHAPES CLASSES ************************//
//----------------------------------------------------------------//

class rectangle : public shape
{
public:
    inline rectangle();
};

class square : public shape
{
public:
    inline square();
};

class circle : public shape
{
public:
    inline circle();
};

class line : public shape
{
public:
    inline line();
};

//---------------------------------------------------------------//
//************************ CTORS & DTORS ************************//
//---------------------------------------------------------------//

inline shape::shape(std::string shape_name) : shape_name(shape_name), offset(0){}

inline shape::shape() : offset(0) {}

inline shape::~shape() {}

inline line::line() : shape("line") {}

inline square::square() : shape("square") {}

inline rectangle::rectangle() : shape("rectangle") {}

inline circle::circle() : shape("circle") {}

//------------------------------------------------------------------//
//************************ MEMBER FUNCTIONS ************************//
//------------------------------------------------------------------//

inline void shape::Draw()
{
    for (int i = 0; i < offset; ++i)
    {
        std::cout << " ";
    }
    std::cout << shape_name << std::endl;
}

inline void shape::Move(int offset) 
{
    this->offset += offset;
}

#endif