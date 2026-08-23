#ifndef ILRD_RD178_COMPLEX_NUMBER_HPP
#define ILRD_RD178_COMPLEX_NUMBER_HPP

#include <iostream> // ostrem, istream

namespace ilrd_178
{
class Complex_Number
{
public:
    
//--------------------------------------------------------------//
//************************ CONSTRUCTORS ************************//
//--------------------------------------------------------------//

    inline Complex_Number(double real = 0, double imaginary = 0) : 
                    real(real), imaginary(imaginary) {}

//---------------------------------------------------------------------//
//************************ SET & GET FUNCTIONS ************************//
//---------------------------------------------------------------------//

    inline void SetReal(double real)
    {
        this->real = real;
    }

    inline void SetImaginary(double imaginary)
    {
          this->imaginary = imaginary;
    }

    inline double GetReal() const
    {
        return real;
    }

    inline double GetImaginary() const
    {
        return imaginary;
    }

//----------------------------------------------------------------------//
//************************ ASSIGNMENT OPERATORS ************************//
//----------------------------------------------------------------------//

    inline Complex_Number& operator+=(const Complex_Number& other) 
    {
        real += other.real;
        imaginary += other.imaginary;

        return *this;
    }

    inline Complex_Number& operator-=(const Complex_Number& other)
    {
        real -= other.real;
        imaginary -= other.imaginary;
        
        return *this;
    }

    inline Complex_Number& operator/=(const Complex_Number& other)
    {
        double r_p1 = this->real;
        double r_p2 = other.real;
        double im_p1 = this->imaginary;
        double im_p2 = other.imaginary;
        double divisor = ((r_p2 * r_p2) + (im_p2 * im_p2));

        this->real = ((r_p1 * r_p2) + (im_p1 * im_p2)) / divisor;
        this->imaginary = ((im_p1 * r_p2) - (r_p1 * im_p2)) / divisor;

        return *this;
    }

    inline Complex_Number& operator*=(const Complex_Number& other)
    {
        double r_p1 = this->real;
        double r_p2 = other.real;
        double im_p1 = this->imaginary;
        double im_p2 = other.imaginary;

        this->real = ((r_p1 * r_p2) - (im_p1 * im_p2));
        this->imaginary = ((im_p1 * r_p2) + (r_p1 * im_p2));

        return *this;
    }


private:
    double real;
    double imaginary;
};

//----------------------------------------------------------------------//
//************************ ARITHMETIC OPERATORS ************************//
//----------------------------------------------------------------------//

inline Complex_Number operator+(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    Complex_Number result(cmplx1);

    return result += cmplx2;
}

inline Complex_Number operator-(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    Complex_Number result(cmplx1);

    return result -= cmplx2;
}

inline Complex_Number operator*(const Complex_Number& cmplx1, const Complex_Number &cmplx2)
{
    Complex_Number result(cmplx1);

    return result *= cmplx2;
}

inline Complex_Number operator/(const Complex_Number& cmplx1, const Complex_Number &cmplx2)
{
    Complex_Number result(cmplx1);

    return result /= cmplx2;
}

//--------------------------------------------------------------------//
//************************ EQUALITY OPERATORS ************************//
//--------------------------------------------------------------------//

inline bool operator==(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    return (cmplx1.GetReal() == cmplx2.GetReal()) 
        && (cmplx1.GetImaginary() == cmplx2.GetImaginary());
}

inline bool operator!=(const Complex_Number& cmplx1, const Complex_Number& cmplx2)
{
    return (cmplx1.GetReal() != cmplx2.GetReal()) 
        || (cmplx1.GetImaginary() != cmplx2.GetImaginary());
}

std::ostream& operator<<(std::ostream &os_, const Complex_Number& cmplx);
std::istream& operator>>(std::istream &is_, Complex_Number& cmplx);

} // namespace ilrd_178

#endif