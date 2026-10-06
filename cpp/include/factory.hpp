#include <functional>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <iostream>

template <typename BASE, typename KEY, typename ... ARGS>
class Factory
{
public:
    using CREATE_FUNC = std::function<std::shared_ptr<BASE>(KEY key, ARGS ... args)>;

    Factory();
    ~Factory();
    
    void Add(const KEY& key, const CREATE_FUNC Creator);
    std::shared_ptr<BASE> Create(const KEY& key, ARGS ... args);

private:
    std::unordered_map<KEY, CREATE_FUNC> m_creators_map;

};
 
template <typename BASE, typename KEY, typename... ARGS>
inline Factory<BASE, KEY, ARGS...>::Factory() {}

template <typename BASE, typename KEY, typename... ARGS>
inline Factory<BASE, KEY, ARGS...>::~Factory() {}

template <typename BASE, typename KEY, typename... ARGS>
inline void Factory<BASE, KEY, ARGS...>::Add(const KEY& key, const CREATE_FUNC Creator) 
{
    m_creators_map.emplace(key, Creator);
}

template <typename BASE, typename KEY, typename... ARGS>
std::shared_ptr<BASE> Factory<BASE, KEY, ARGS...>::Create(const KEY &key, ARGS... args)
{
    std::shared_ptr<BASE> object;
    try
    {
        CREATE_FUNC creator = m_creators_map.at(key);
        object = (creator(key, args ...));
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    return object;
}
