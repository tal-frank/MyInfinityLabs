#ifndef ood_file_dir_H
#define ood_file_dir_H

#include <string> /* std::string */
#include <vector> /* vector */

namespace ilrd_178
{

class FileComponent
{
public:
    explicit inline FileComponent(const std::string& file_name) 
                                 : m_name(file_name) {}
    virtual ~FileComponent() = 0;
    virtual void Print(size_t depth = 0) const;
    virtual FileComponent* clone() = 0;

protected:
    inline FileComponent(const FileComponent& other_) 
                         : m_name(other_.m_name) {}
    FileComponent operator=(const FileComponent& file_comp);
    
private:
    std::string m_name;
};

class Dir : public FileComponent
{
public:
    explicit inline Dir(const std::string& file_name) 
                        : FileComponent(file_name) {}
    virtual ~Dir();
    virtual void Print(size_t depth = 0) const;
    virtual void Add(FileComponent* to_insert);
    virtual void Delete(const FileComponent* to_delete);
    virtual FileComponent* clone();

protected:
    Dir(const Dir& other_);
    Dir& operator=(const Dir& other_);
    
private:
    std::vector<FileComponent*> m_children;
};

class File : public FileComponent
{
public:
    explicit inline File(const std::string& file_name) 
                         : FileComponent(file_name) {}
    virtual inline ~File() {}
    void Print(size_t depth = 0) const;
    virtual FileComponent* clone();
    
private:
    File(const File& file);
};

} // namespace ilrd_178
#endif /* ood_file_dir_H */