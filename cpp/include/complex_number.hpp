#ifndef ILRD_RD178_COMPLEX_NUMBER_HPP
#define ILRD_RD178_COMPLEX_NUMBER_HPP

#include <iostream> // ostrem, istream

namespace ilrd_178
{
class Complex_Number
{
public:
    Complex_Number(double real = 0, double imaginary = 0);

    Complex_Number& operator+=(const Complex_Number &other);
    Complex_Number& operator-=(const Complex_Number &other);
    Complex_Number& operator*=(const Complex_Number &other);
    Complex_Number& operator/=(const Complex_Number &other);
    
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

private:
    double real;
    double imaginary;
};

bool operator==(const Complex_Number& cmplx1, const Complex_Number& cmplx2);
bool operator!=(const Complex_Number& cmplx1, const Complex_Number& cmplx2);
std::ostream& operator<<(std::ostream &os_, const Complex_Number &cmplx);
std::istream& operator>>(std::istream &is_, Complex_Number &cmplx);

Complex_Number operator+(const Complex_Number& cmplx1, const Complex_Number &cmplx2);
Complex_Number operator-(const Complex_Number& cmplx1, const Complex_Number &cmplx2);
Complex_Number operator*(const Complex_Number& cmplx1, const Complex_Number &cmplx2);
Complex_Number operator/(const Complex_Number& cmplx1, const Complex_Number &cmplx2);

} // namespace ilrd_178

#endif