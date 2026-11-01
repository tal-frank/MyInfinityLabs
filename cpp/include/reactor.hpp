/**********************
* reactor
* Author: Tal Frank
* Reviewer: 
* Last update: 29/10/2026
**********************/

#ifndef ILRD_178_REACTOR
#define ILRD_178_REACTOR

#include <map>           // unordered_map
#include <vector>        // vector
#include <functional>    // std::function
#include <memory>        // unique_ptr

namespace ilrd_178
{

enum RW_Mode
{
    read_op,
    write_op
};

class SelectorKind
{
public:
    virtual ~SelectorKind() = default;

    virtual void Add(std::pair<int, RW_Mode> fd) = 0;
    virtual void Remove(std::pair<int, RW_Mode> fd) = 0;

    virtual std::vector<std::pair<int, RW_Mode> > Selector() = 0;
};

class Reactor
{
public:
    explicit Reactor(SelectorKind* selector);
    ~Reactor() = default;

    Reactor(const Reactor&) = delete;
    Reactor& operator=(const Reactor&) = delete;

    void Add(std::pair<int, RW_Mode> fd, std::function<void()> callback);
    void Remove(std::pair<int, RW_Mode> fd);

    void Run();
    void Stop();

private:
    bool m_is_running;
    std::unique_ptr<SelectorKind> m_selector;
    std::map<std::pair<int, RW_Mode>, std::function<void()> > m_events_map;
};
}

#endif