/**********************
* priority queue
* Author: Tal Frank
* Reviewer: 
* Last update: 27/09/2026
**********************/

#ifndef ILRD_178_PRIORITY_QUEUE_HPP
#define ILRD_178_PRIORITY_QUEUE_HPP

#include <functional>  // less
#include <queue>       // queue
#include <vector>      // vector

namespace ilrd_178
{
    
template < typename T, typename CONTAINER = std::vector<T>, typename COMPARE = std::less<T> >
class PriorityQueue : private std::priority_queue<T,CONTAINER,COMPARE>
{

public:
    using const_reference = typename CONTAINER::const_reference;
    using pq = std::priority_queue<T,CONTAINER,COMPARE>;
    
    using pq::empty;
    using pq::pop;
    using pq::push;
    using pq::size;
    const_reference front() const { return pq::top(); }
    
};

} // namespace ilrd_178

#endif // ILRD_178_PRIORITY_QUEUE_HPP	