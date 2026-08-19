#include <ctime>

#include "complex_number.hpp"

using namespace ilrd_178;

int main()
{
    Complex_Number cmplx1;

    std::cout << "cmplx1 = " << cmplx1 << std::endl;

    Complex_Number cmplx2(2, 2);
    Complex_Number cmplx3(1, 3);

    std::cout << "cmplx2 = " << cmplx2 << ", cmplx3 = " << cmplx3 << std::endl;

    Complex_Number cmplx4 = cmplx2 + cmplx3;
    std::cout << "cmplx2 + cmplx3 = " << cmplx4 << std::endl;

    Complex_Number cmplx5 = cmplx2 - cmplx3;
    std::cout << "cmplx2 - cmplx3 = " << cmplx5 << std::endl;

    Complex_Number cmplx6 = cmplx2 * cmplx3;
    std::cout << "cmplx2 * cmplx3 = " << cmplx6 << std::endl;

    Complex_Number cmplx7 = cmplx2 / cmplx3;
    std::cout << "cmplx2 / cmplx3 = " << cmplx7 << std::endl;

    Complex_Number cmplx8(cmplx2);
    std::cout << "cmplx8 = cmplx2 = " << cmplx8 << std::endl;

    cmplx8 += cmplx3;
    std::cout << "cmplx8 += cmplx3 -> " << cmplx8 << std::endl;
    cmplx8 = cmplx2;

    cmplx8 -= cmplx3;
    std::cout << "cmplx8 -= cmplx3 -> " << cmplx8 << std::endl;
    cmplx8 = cmplx2;

    cmplx8 *= cmplx3;
    std::cout << "cmplx8 *= cmplx3 -> " << cmplx8 << std::endl;
    cmplx8 = cmplx2;

    cmplx8 /= cmplx3;
    std::cout << "cmplx8 /= cmplx3 -> " << cmplx8 << std::endl;
    cmplx8 = cmplx2;

    if (cmplx8 == cmplx2)
    {
        std::cout << "operator '==' check : cmplx8 is equal to cmplx2." << std::endl;
    }

    if (!(cmplx8 != cmplx2))
    {
        std::cout << "operator '!=' check : cmplx8 is equal to cmplx2." << std::endl;
    }

    if (!(cmplx8 == cmplx3))
    {
        std::cout << "operator '==' check : cmplx8 is not equal to cmplx3." << std::endl;
    }

    if (cmplx8 != cmplx3)
    {
        std::cout << "operator '!=' check : cmplx8 is not equal to cmplx3." << std::endl;
    }

    if (cmplx1 == 0)
    {
        std::cout << "operator '==' implicit check : cmplx1 is equal to 0." << std::endl;
    }

    if (0 == cmplx1)
    {
        std::cout << "operator '==' implicit check : 0 is equal to cmplx1." << std::endl;
    }

    cmplx1 = cmplx2;
    if (!(0 == cmplx1))
    {
        std::cout << "operator '==' implicit check : 0 is not equal to cmplx1." << std::endl;
    }

    if (0 != cmplx1)
    {
        std::cout << "operator '==' implicit check : 0 is not equal to cmplx1." << std::endl;
    }

    time_t start = clock();
    for (size_t i = 0; i < 100000; ++i)
    {
        cmplx1 = cmplx2 +cmplx3;
    }
    time_t end = clock();
    std::cout << "time for 100k times operator + is : " << 1000 * (double(end - start)) / CLOCKS_PER_SEC << "ms" << std::endl;

    // std::cin >> cmplx8;
    // std::cout << "cmplx8 = " << cmplx8 << std::endl;
    // cmplx8 = cmplx2;

    return 0;
}