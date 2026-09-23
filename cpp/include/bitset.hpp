#ifndef ILRD_178_BITSET_HPP
#define ILRD_178_BITSET_HPP

#include <cstddef> // size_t
#include <algorithm> //
#include <string> // string type
#include <cstring> // memcpy

//------------------------------------------------------------------//
//************************ CLASS DEFINITION ************************//
//------------------------------------------------------------------//

const int BYTE_SIZE_IN_BITS = sizeof(char) * 8;

namespace ilrd_178
{

    template <size_t SIZE>
class BitSet
{
private:
    class BitProxy;
    
public:
    explicit BitSet();
    BitSet(const BitSet& other);
    BitSet& operator=(const BitSet& other);
    ~BitSet();
    
    BitSet& operator^=(const BitSet& bs); 
    BitSet& operator&=(const BitSet& bs);
    BitSet& operator|=(const BitSet& bs);
    
    bool operator!=(const BitSet& bs) const; // todo
    bool operator==(const BitSet& bs) const; // todo
    
    std::string ToString() const;
        
    BitProxy operator[](size_t indx);
    bool operator[](size_t indx) const;

private:
    class BitProxy
    {
    public:
        explicit BitProxy(BitSet& bitset, size_t indx);
        
        BitProxy& operator=(bool x);
        BitProxy& operator=(const BitProxy& BitProxy);
        
        operator bool() const;
        
    private:
        BitSet& m_bitset;
        size_t m_indx;
    };
    
    char m_bitmap[((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1];
};

template<size_t SIZE>
BitSet<SIZE>& operator^(const BitSet<SIZE>& bs1, const BitSet<SIZE>& bs2); // todo
template<size_t SIZE>
BitSet<SIZE>& operator!=(const BitSet<SIZE>& bs1, const BitSet<SIZE>& bs2); // todo
template<size_t SIZE>
BitSet<SIZE>& operator&(const BitSet<SIZE>& bs1, const BitSet<SIZE>& bs2); // todo
template<size_t SIZE>
BitSet<SIZE>& operator|(const BitSet<SIZE>& bs1, const BitSet<SIZE>& bs2); // todo


template<size_t SIZE>
BitSet<SIZE>::BitSet()
{
    std::fill(m_bitmap, m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1, 0);
}

template<size_t SIZE>
BitSet<SIZE>::BitSet(const BitSet& other) 
{
    memcpy(m_bitmap, other.m_bitmap, ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1);
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator=(const BitSet& other) 
{
    if (this != &other)
    {
        memcpy(m_bitmap, other.m_bitmap, ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1);
    }
    return *this;
}

template<size_t SIZE>
BitSet<SIZE>::~BitSet() {}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator^=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_xor<char>());
    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator&=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_and<char>());
    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator|=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_or<char>());
    return *this;
}
    
// template<size_t SIZE>  
// bool BitSet<SIZE>::operator!=(const BitSet& bs) const {}

// template<size_t SIZE>
// bool BitSet<SIZE>::operator==(const BitSet& bs) const {}

template<size_t SIZE>
std::string BitSet<SIZE>::ToString() const 
{
    std::string bit_str = "";
    char byte = 0;
    char mask = 1;
    for (size_t i = 0; i < ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1; ++i)
    {
        byte = m_bitmap[i];
        mask = 1;
        for (size_t j = 0; j < BYTE_SIZE_IN_BITS; ++j)
        {
            bit_str += (byte & mask) ? '1' : '0';
            mask <<= 1;
        }
        bit_str += '\n';
    }
    return bit_str;
}

template<size_t SIZE>
bool BitSet<SIZE>::operator[](size_t indx) const 
{
    size_t byte_index = indx / (BYTE_SIZE_IN_BITS);
    size_t bit_index = indx % (BYTE_SIZE_IN_BITS);
    char mask = 1 << bit_index - 1;
    return !!(m_bitmap[byte_index] & mask);
}

template<size_t SIZE>
typename BitSet<SIZE>::BitProxy BitSet<SIZE>::operator[](size_t indx) 
{
    return BitProxy(*this, indx);
}

template <size_t SIZE>
inline BitSet<SIZE>::BitProxy::BitProxy(BitSet &bitset, size_t indx) : m_bitset(bitset), m_indx(indx) {}

template <size_t SIZE>
inline typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=(bool x)
{
    char mask = 1 << (m_indx % BYTE_SIZE_IN_BITS);
    
    false == x ? m_bitset.m_bitmap[m_indx / BYTE_SIZE_IN_BITS] &= ~mask
               : m_bitset.m_bitmap[m_indx / BYTE_SIZE_IN_BITS] |= mask;
    
    return *this;
}

template <size_t SIZE>
inline typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=(const BitProxy &BitProxy)
{
    char mask = 0x01 << (BitProxy.m_indx % BYTE_SIZE_IN_BITS);
    bool bit = !!(mask & BitProxy.m_bitset.m_bitmap[BitProxy.m_indx / BYTE_SIZE_IN_BITS]);
    mask = 1 << (m_indx % BYTE_SIZE_IN_BITS);

    false == bit ? m_bitset.m_bitmap[m_indx / BYTE_SIZE_IN_BITS] &= ~mask
                 : m_bitset.m_bitmap[m_indx / BYTE_SIZE_IN_BITS] |= mask;
    
    return *this;
}

}

#endif // ILRD_178_BITSET_HPP