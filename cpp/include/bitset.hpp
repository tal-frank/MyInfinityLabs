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

const int num_of_bits_on_lut[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
const int BYTE_SIZE_IN_BITS = sizeof(char) * 8;

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
    
    unsigned char m_bitmap[((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1];
};

static char FlipBits(char byte);

//--------------------------------------------------------------//
//************************ CONSTRUCTORS ************************//
//--------------------------------------------------------------//

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
        memcpy(m_bitmap, other.m_bitmap, ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1);
    }
    return *this;
}

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



template<size_t SIZE>
bool BitSet<SIZE>::operator[](size_t indx) const 
{
    size_t byte_index = indx / (BYTE_SIZE_IN_BITS);
    size_t bit_index = indx % (BYTE_SIZE_IN_BITS);
    char mask = 1 << bit_index;
    return !!(m_bitmap[byte_index] & mask);
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


template<size_t SIZE>
void BitSet<SIZE>::FlipBit(size_t indx)
{
    unsigned char mask = (1 << ((indx % BYTE_SIZE_IN_BITS)));
    m_bitmap[(indx - 1) / BYTE_SIZE_IN_BITS] ^= mask;
}

template<size_t SIZE>
void BitSet<SIZE>::FlipAll()
{
    std::transform(m_bitmap, 
                   m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS),
                   m_bitmap,
                   std::ptr_fun(FlipBits));

    if (0 != SIZE % BYTE_SIZE_IN_BITS)
    {
        unsigned char mask = (1 << (SIZE % BYTE_SIZE_IN_BITS)) - 1;
        m_bitmap[(SIZE - 1) / BYTE_SIZE_IN_BITS] ^= mask;
    }
}

//--------------------------------------------------------------------//
//************************ EQUALITY OPERATORS ************************//
//--------------------------------------------------------------------//

template<size_t SIZE>  
bool BitSet<SIZE>::operator==(const BitSet& bs) const 
{
    return std::equal(m_bitmap, m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1, bs.m_bitmap);
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
              m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS), 
              val ? 0xFF : 0x00);

    if (0 != SIZE % BYTE_SIZE_IN_BITS)
    {
        unsigned char mask = (1 << (SIZE % BYTE_SIZE_IN_BITS)) - 1;
        false == val ? m_bitmap[(SIZE - 1) / BYTE_SIZE_IN_BITS] &= ~mask
                     : m_bitmap[(SIZE - 1) / BYTE_SIZE_IN_BITS] |= mask;
    }
}

template <size_t SIZE>
inline void BitSet<SIZE>::SetBit(bool val, size_t indx)
{
    char mask = 1 << (indx % BYTE_SIZE_IN_BITS);
    false == val ? m_bitmap[indx / BYTE_SIZE_IN_BITS] &= ~mask
                 : m_bitmap[indx / BYTE_SIZE_IN_BITS] |= mask;
}

template <size_t SIZE>
inline bool BitSet<SIZE>::GetBit(size_t indx) const
{
    char mask = 1 << (indx % BYTE_SIZE_IN_BITS);
    char byte = m_bitmap[indx / BYTE_SIZE_IN_BITS];

    return !!(byte & mask);
}

//------------------------------------------------------------------//
//************************ STATIC FUNCTIONS ************************//
//------------------------------------------------------------------//

static char FlipBits(char byte)
{
    return ~byte;
}

static size_t OnBits(size_t total_cnt, unsigned char part_val)
{
    return total_cnt + num_of_bits_on_lut[0x0F & part_val] + num_of_bits_on_lut[part_val >> 4];
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
    return std::accumulate(m_bitmap, m_bitmap + ((SIZE - 1) / BYTE_SIZE_IN_BITS) + 1, 0, std::ptr_fun(OnBits));
}

template <size_t SIZE>
inline BitSet<SIZE>::BitProxy::operator bool() const
{
    char mask = 1 << (m_indx % BYTE_SIZE_IN_BITS);
    char byte = m_bitset.m_bitmap[m_indx / BYTE_SIZE_IN_BITS];
    return !!(byte &= mask);
}

}


#endif // ILRD_178_BITSET_HPP