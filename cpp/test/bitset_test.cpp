#include <bitset.hpp>
#include <iostream>

using namespace ilrd_178;

int main()
{
    BitSet<10> bs;

    bs[9] = true;
    std::cout << bs.ToString() << std::endl;

    bs[3] = bs[9];
    std::cout << bs.ToString() << std::endl;

    bs[2] = bs [6];
    std::cout << bs.ToString() << std::endl;

    BitSet<10> bs10;

    bs10[8] = true;
    bs[5] = bs10[8];
    std::cout << bs10.ToString() << std::endl;
    std::cout << bs.ToString() << std::endl;
    
    bs[5] = bs10[4];
    std::cout << bs.ToString() << std::endl;
    
    bs[2] = true;
    bs[7] = true;
    
    bs[9] = false;
    std::cout << bs.ToString() << std::endl;

    bs10 = bs;
    std::cout << bs10.ToString() << std::endl;

    BitSet<10> bs_new(bs10);
    std::cout << bs_new.ToString() << std::endl;

    BitSet<10> bs_xor;

    bs_xor[0] = true;
    bs_xor[2] = true;
    bs_xor ^= bs;
    std::cout << bs_xor.ToString() << std::endl;

    BitSet<10> bs_or;

    bs_or[0] = true;
    bs_or[2] = true;
    bs_or |= bs;
    std::cout << bs_or.ToString() << std::endl;

    BitSet<10> bs_and;

    bs_and[0] = true;
    bs_and[2] = true;
    bs_and &= bs;
    std::cout << bs_and.ToString() << std::endl;

    return 0;
}