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