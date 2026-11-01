#include <cstddef>   // size_t
#include <algorithm> // find
#include <stdexcept> // runtime_error

#include "reactor.hpp"

namespace ilrd_178
{

Reactor::Reactor(SelectorKind* selector) : m_is_running(false),
                                           m_selector(selector)  {}

void Reactor::Add(std::pair<int, RW_Mode> fd, std::function<void()> callback)
{
    m_events_map[fd] = callback;
    m_selector->Add(fd);
}

void Reactor::Remove(std::pair<int, RW_Mode> fd)
{
    m_events_map.erase(fd);
    m_selector->Remove(fd);
}

void Reactor::Run()
{
    if (m_is_running)
    {
        throw std::runtime_error("Reactor is already running.");
    }

    m_is_running = true;

    while (m_is_running)
    {
        std::vector<std::pair<int, RW_Mode> > active_events_vec = m_selector->Selector();

        for (std::pair<int, RW_Mode> fd : active_events_vec)
        {
            if (!m_is_running)
            {
                break;
            }

            if (m_events_map.end() != m_events_map.find(fd))
            {
                std::function<void()> callback = m_events_map[fd];
                callback();
            }
        }
    }
}

void Reactor::Stop()
{
    m_is_running = false;
}

}
