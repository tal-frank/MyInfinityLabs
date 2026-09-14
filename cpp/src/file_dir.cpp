#include <iostream>
#include <algorithm>

#include "file_dir.hpp"

namespace ilrd_178
{

//---------------------------------------------------------------------------------------//
//############################# FILECOMPONENT FUNCTIONS #################################//
//---------------------------------------------------------------------------------------//

FileComponent::~FileComponent() {}

void FileComponent::Print(size_t depth) const
{
    for(size_t i = 0; i < depth; ++i)
    {
        std::cout << "|  ";
    }
    std::cout << "+-" << m_name << std::endl;
}

//-----------------------------------------------------------------------------//
//############################# DIR FUNCTIONS #################################//
//-----------------------------------------------------------------------------//

void Dir::Print(size_t depth) const
{
    FileComponent::Print(depth++);
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        m_children[i]->Print(depth);
    }
}

Dir::Dir(const Dir& other_) : FileComponent(other_)
{
    for(size_t i = 0; i < other_.m_children.size(); ++i)
    {
        this->m_children.push_back(other_.m_children[i]);
        this->m_children[i] = other_.m_children[i]->clone();
    }
}

void Dir::Add(FileComponent* to_insert)
{
    m_children.push_back(to_insert);
}

void Dir::Delete(const FileComponent* to_delete)
{
    std::vector<FileComponent*>::iterator iter_to_delete = m_children.begin();
    iter_to_delete = std::find(m_children.begin(), m_children.end(), to_delete);
    if (iter_to_delete != m_children.end())
    {
        iter_to_delete = m_children.erase(iter_to_delete);
    }
}

FileComponent* Dir::clone()
{
    return new Dir(*this);
}

//------------------------------------------------------------------------------//
//############################# FILE FUNCTIONS #################################//
//------------------------------------------------------------------------------//

File::File(const File& other_) : FileComponent(other_) {}

void File::Print(size_t depth) const
{
    FileComponent::Print(depth);
}

FileComponent* File::clone()
{
    return new File(*this);
}

}