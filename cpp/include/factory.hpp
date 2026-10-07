/**********************
* factory
* Author: Tal Frank
* Reviewer: Almog Nimni
* Last update: 07/10/2026
**********************/

#ifndef __ILRD_178__FACTORY__HPP__
#define __ILRD_178__FACTORY__HPP__

#include <functional>    // std::function
#include <unordered_map> // unordered map 
#include <memory>        // shared_ptr
 
namespace ilrd_178
{
template <typename BASE, typename KEY, typename ... ARGS>
class Factory
{
public:
    using CREATE_FUNC = std::function<std::shared_ptr<BASE>(ARGS ... args)>;

    Factory() = default;
    ~Factory() = default;
    
    void Add(const KEY& key, CREATE_FUNC Creator);
    std::shared_ptr<BASE> Create(const KEY& key, ARGS ... args) const;

    struct InvalidKey : public std::runtime_error 
    {
    public:
        InvalidKey(const char* str) : runtime_error(str) {}
    };

private:
    std::unordered_map<KEY, CREATE_FUNC> m_creators_map;

};

template <typename BASE, typename KEY, typename... ARGS>
inline void Factory<BASE, KEY, ARGS...>::Add(const KEY& key, CREATE_FUNC Creator) 
{
    m_creators_map[key] = Creator;
}

template <typename BASE, typename KEY, typename... ARGS>
std::shared_ptr<BASE> Factory<BASE, KEY, ARGS...>::Create(const KEY &key, ARGS... args) const
{
    std::shared_ptr<BASE> object;
    CREATE_FUNC creator;
    try
    {
        creator = m_creators_map.at(key);
    }
    catch(const std::out_of_range& e) 
    {
        throw InvalidKey("key not found");
    }

    object = (creator(args ...));
    return object;
}
}

#endif