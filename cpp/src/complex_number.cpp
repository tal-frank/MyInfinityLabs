/**********************
* complex number
* Author: Tal Frank
* Reviewer: Yael Novick
* Last update: 19/08/2026
**********************/

#include <iostream>

#include "complex_number.hpp"

namespace ilrd_178
{
//--------------------------------------------------------------//
//************************ CONSTRUCTORS ************************//
//--------------------------------------------------------------//

Complex_Number::Complex_Number(double real, double imaginary) : 
                real(real), imaginary(imaginary) {}

//----------------------------------------------------------------------//
//************************ ASSIGNMENT OPERATORS ************************//
//----------------------------------------------------------------------//

Complex_Number& Complex_Number::operator+=(const Complex_Number& other) 
{
    real += other.real;
    imaginary += other.imaginary;

    return *this;
}

Complex_Number& Complex_Number::operator-=(const Complex_Number& other)
{
    real -= other.real;
    imaginary -= other.imaginary;
    
    return *this;
}

Complex_Number& Complex_Number::operator/=(const Complex_Number& other)
{
    double r_p1 = this->real;
    double r_p2 = other.real;
    double im_p1 = this->imaginary;
    double im_p2 = other.imaginary;
    double divisor = ((r_p2 * r_p2) + (im_p2 * im_p2));

    double r_result = ((r_p1 * r_p2) + (im_p1 * im_p2)) / divisor;
    double i_result = ((im_p1 * r_p2) - (r_p1 * im_p2)) / divisor;

    this->real = r_result;
    this->imaginary = i_result;

    return *this;
}

Complex_Number& Complex_Number::operator*=(const Complex_Number& other)
{
    double r_p1 = this->real;
    double r_p2 = other.real;
    double im_p1 = this->imaginary;
    double im_p2 = other.imaginary;

    double r_result = ((r_p1 * r_p2) - (im_p1 * im_p2));
    double i_result = ((im_p1 * r_p2) + (r_p1 * im_p2));

    this->real = r_result;
    this->imaginary = i_result;

    return *this;
}

//----------------------------------------------------------------------//
//************************ ARITHMETIC OPERATORS ************************//
//----------------------------------------------------------------------//

Complex_Number operator+(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    Complex_Number result(cmplx1);

    return result += cmplx2;
}

Complex_Number operator-(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    Complex_Number result(cmplx1);

    return result -= cmplx2;
}

Complex_Number operator*(const Complex_Number& cmplx1, const Complex_Number &cmplx2)
{
    Complex_Number result(cmplx1);

    return result *= cmplx2;
}

Complex_Number operator/(const Complex_Number& cmplx1, const Complex_Number &cmplx2)
{
    Complex_Number result(cmplx1);

    return result /= cmplx2;
}

//--------------------------------------------------------------------//
//************************ EQUALITY OPERATORS ************************//
//--------------------------------------------------------------------//

bool operator==(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    return (cmplx1.GetReal() == cmplx2.GetReal()) 
        && (cmplx1.GetImaginary() == cmplx2.GetImaginary());
}

bool operator!=(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    return (cmplx1.GetReal() != cmplx2.GetReal()) 
        || (cmplx1.GetImaginary() != cmplx2.GetImaginary());
}

//----------------------------------------------------------------------//
//************************ I/O stream OPERATORS ************************//
//----------------------------------------------------------------------//

std::ostream& operator<<(std::ostream &os_, const Complex_Number &cmplx)
{
    return os_ << cmplx.GetReal() << "+(" << cmplx.GetImaginary() << ")i";
}

std::istream& operator>>(std::istream &is_, Complex_Number &cmplx)
{
    double temp;

    is_ >> temp;
    cmplx.SetReal(temp);
    
    is_ >> temp;
    cmplx.SetImaginary(temp);

    return is_;
}
}