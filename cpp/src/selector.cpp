#include <sys/select.h> // fd_set
#include <unistd.h>     // ssize_t

#include "selector.hpp"

namespace ilrd_178
{
Select::Select() : m_max_fd(-1)
{
    FD_ZERO(&m_read_events);
    FD_ZERO(&m_write_events);
}

void Select::Add(std::pair<int, RW_Mode> fd)
{
    read_op == fd.second ? FD_SET(fd.first, &m_read_events)
                         : FD_SET(fd.first, &m_write_events);
    
    if (fd.first > m_max_fd)
    {
        m_max_fd = fd.first;
    }
}

void Select::Remove(std::pair<int, RW_Mode> fd)
{
    read_op == fd.second ? FD_CLR(fd.first, &m_read_events)
                      : FD_CLR(fd.first, &m_write_events);

    if (fd.first == m_max_fd)
    {
        int i = fd.first - 1;
        for(; i > -1 ; --i)
        {
            if (FD_ISSET(i, &m_read_events) || FD_ISSET(i, &m_write_events))
            {
                m_max_fd = i;
                break;
            }
        }
        if  (-1 == i)
        {
            m_max_fd = i;
        }
    }
}

std::vector<std::pair<int, RW_Mode> > Select::Selector()
{
    std::vector<std::pair<int, RW_Mode> > active_events_vec;

    if (0 > m_max_fd)
    {
        return active_events_vec;
    }

    fd_set active_read_events = m_read_events;
    fd_set active_write_events = m_write_events;

    ssize_t num_active_fd = select(m_max_fd + 1, 
                                   &active_read_events, 
                                   &active_write_events, 
                                   nullptr, 
                                   nullptr);
    if (0 > num_active_fd)
    {
        return active_events_vec;
    }

    for (ssize_t fd = 0; fd <= m_max_fd; ++fd)
    {
        std::pair<int, RW_Mode> fd_pair;
        fd_pair.first = fd;

        if (FD_ISSET(fd, &active_read_events))
        {
            fd_pair.second = read_op;
            active_events_vec.push_back(fd_pair);
        }
        if (FD_ISSET(fd, &active_write_events))
        {
            fd_pair.second = write_op;
            active_events_vec.push_back(fd_pair);
        }
    }
    
    return active_events_vec;
}
}