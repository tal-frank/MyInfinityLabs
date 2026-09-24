/**********************
* bitset
* Author: Tal Frank
* Reviewer: Moshe Moiseev
* Last update: 24/09/2026
**********************/

#ifndef ILRD_178_BITSET_HPP
#define ILRD_178_BITSET_HPP

#include <cstddef> // size_t
#include <algorithm> // fill , transform
#include <string> // string type
#include <cstring> // memcpy
#include <numeric> // accumulate

//------------------------------------------------------------------//
//************************ GLOBAL CONSTANTS ************************//
//------------------------------------------------------------------//

const int NUM_OF_BITS_IN_BYTE = sizeof(char) * 8;

//------------------------------------------------------------------//
//************************ CLASS DEFINITION ************************//
//------------------------------------------------------------------//

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
    void SetAll(bool val);
    void SetBit(bool val, size_t indx); 
    bool GetBit(size_t indx) const;
    void FlipBit(size_t indx);
    void FlipAll();
    size_t CountOn() const;
    
    bool operator!=(const BitSet& bs) const;
    bool operator==(const BitSet& bs) const;
    
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
    
    unsigned char m_bitmap[((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1];
};

//----------------------------------------------------------//
//************************ FUNCTORS ************************//
//----------------------------------------------------------//

struct OnBits
{
public:
    size_t operator()(size_t total_cnt, unsigned char part_val)
    {
        return total_cnt + num_of_bits_on_lut[0x0F & part_val] + num_of_bits_on_lut[part_val >> 4];
    }
private:
    static const int num_of_bits_on_lut[16];

};

const int OnBits::num_of_bits_on_lut[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

//--------------------------------------------------------------//
//************************ CONSTRUCTORS ************************//
//--------------------------------------------------------------//

template<size_t SIZE>
BitSet<SIZE>::BitSet()
{
    std::fill(m_bitmap, m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1, 0);
}

template<size_t SIZE>
BitSet<SIZE>::BitSet(const BitSet& other) 
{
    memcpy(m_bitmap, other.m_bitmap, ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1);
}

template <size_t SIZE>
inline BitSet<SIZE>::BitProxy::BitProxy(BitSet &bitset, size_t indx) : m_bitset(bitset), m_indx(indx) {}

//----------------------------------------------------------------------//
//************************ ASSIGNMENT OPERATORS ************************//
//----------------------------------------------------------------------//

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator=(const BitSet& other) 
{
    if (this != &other)
    {
        memcpy(m_bitmap, other.m_bitmap, ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1);
    }
    return *this;
}

template <size_t SIZE>
inline typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=(bool x)
{   
    this->m_bitset.SetBit(x, m_indx);
    
    return *this;
}

template <size_t SIZE>
inline typename BitSet<SIZE>::BitProxy& BitSet<SIZE>::BitProxy::operator=(const BitProxy &BitProxy)
{
    const char mask = 0x01 << (BitProxy.m_indx % NUM_OF_BITS_IN_BYTE);
    bool bit = !!(mask & BitProxy.m_bitset.m_bitmap[BitProxy.m_indx / NUM_OF_BITS_IN_BYTE]);

    this->m_bitset.SetBit(bit, m_indx);
    
    return *this;
}

template<size_t SIZE>
bool BitSet<SIZE>::operator[](size_t indx) const 
{
    return this->GetBit(indx);
}

template<size_t SIZE>
typename BitSet<SIZE>::BitProxy BitSet<SIZE>::operator[](size_t indx) 
{
    return BitProxy(*this, indx);
}

//-------------------------------------------------------------------//
//************************ BITWISE OPERATORS ************************//
//-------------------------------------------------------------------//

template<size_t SIZE>
BitSet<SIZE>::~BitSet() {}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator^=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_xor<char>());
    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator&=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_and<char>());
    return *this;
}

template<size_t SIZE>
BitSet<SIZE>& BitSet<SIZE>::operator|=(const BitSet& bs) 
{
    std::transform(bs.m_bitmap, 
                   bs.m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1,
                   m_bitmap,
                   m_bitmap,
                   std::bit_or<char>());
    return *this;
}


template<size_t SIZE>
void BitSet<SIZE>::FlipBit(size_t indx)
{
    const unsigned char mask = (1 << ((indx % NUM_OF_BITS_IN_BYTE)));
    m_bitmap[(indx - 1) / NUM_OF_BITS_IN_BYTE] ^= mask;
}

template<size_t SIZE>
void BitSet<SIZE>::FlipAll()
{
    std::transform(m_bitmap, 
                   m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE),
                   m_bitmap,
                   std::bit_not<char>());

    if (0 != SIZE % NUM_OF_BITS_IN_BYTE)
    {
        const unsigned char mask = (1 << (SIZE % NUM_OF_BITS_IN_BYTE)) - 1;
        m_bitmap[(SIZE - 1) / NUM_OF_BITS_IN_BYTE] ^= mask;
    }
}

//--------------------------------------------------------------------//
//************************ EQUALITY OPERATORS ************************//
//--------------------------------------------------------------------//

template<size_t SIZE>  
bool BitSet<SIZE>::operator==(const BitSet& bs) const 
{
    return std::equal(m_bitmap, m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1, bs.m_bitmap);
}

template<size_t SIZE>
bool BitSet<SIZE>::operator!=(const BitSet& bs) const 
{
    return !(*this == bs);
}

//-------------------------------------------------------------------//
//************************ GETTERS & SETTERS ************************//
//-------------------------------------------------------------------//

template<size_t SIZE>
void BitSet<SIZE>::SetAll(bool val)
{
    std::fill(m_bitmap,
              m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE), 
              val ? static_cast<char>(~0) : static_cast<char>(0));

    if (0 != SIZE % NUM_OF_BITS_IN_BYTE)
    {
        const unsigned char mask = (1 << (SIZE % NUM_OF_BITS_IN_BYTE)) - 1;
        false == val ? m_bitmap[(SIZE - 1) / NUM_OF_BITS_IN_BYTE] &= ~mask
                     : m_bitmap[(SIZE - 1) / NUM_OF_BITS_IN_BYTE] |= mask;
    }
}

template <size_t SIZE>
inline void BitSet<SIZE>::SetBit(bool val, size_t indx)
{
    const char mask = 1 << (indx % NUM_OF_BITS_IN_BYTE);
    false == val ? m_bitmap[indx / NUM_OF_BITS_IN_BYTE] &= ~mask
                 : m_bitmap[indx / NUM_OF_BITS_IN_BYTE] |= mask;
}

template <size_t SIZE>
inline bool BitSet<SIZE>::GetBit(size_t indx) const
{
    const char mask = 1 << (indx % NUM_OF_BITS_IN_BYTE);
    const char byte = m_bitmap[indx / NUM_OF_BITS_IN_BYTE];

    return !!(byte & mask);
}

//-----------------------------------------------------------------//
//************************ OTHER FUNCTIONS ************************//
//-----------------------------------------------------------------//

template<size_t SIZE>
std::string BitSet<SIZE>::ToString() const 
{
    std::string bit_str = "";
    for(size_t i = 0; i < SIZE; ++i)
    {
        bit_str += 0 == (*this)[i] ? '0' : '1';
    }
    return bit_str;
}

template <size_t SIZE>
inline size_t BitSet<SIZE>::CountOn() const
{
    return std::accumulate(m_bitmap, m_bitmap + ((SIZE - 1) / NUM_OF_BITS_IN_BYTE) + 1, 0, OnBits());
}

template <size_t SIZE>
inline BitSet<SIZE>::BitProxy::operator bool() const
{
    return this->m_bitset.GetBit(m_indx);
}

}


#endif // ILRD_178_BITSET_HPP