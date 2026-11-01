#ifndef ILRD_178_SELECTOR
#define ILRD_178_SELECTOR

#include "reactor.hpp"

namespace ilrd_178
{

class Select : public SelectorKind
{
public :
    Select();
    ~Select() override = default;

    void Add(std::pair<int, RW_Mode> fd);
    void Remove(std::pair<int, RW_Mode> fd);

    std::vector<std::pair<int, RW_Mode> > Selector();

private:
    fd_set m_read_events;
    fd_set m_write_events;
    int m_max_fd;
};
}

#endif