#include <dlfcn.h>  // dlopen
#include <unistd.h> // close
#include <iostream>

#include "dll_loader.hpp"

const ssize_t NO_FILE = -1;

namespace ilrd_178
{

//-----------------------------------------------------------------------------------//
//################################# DIR MONITOR #####################################//
//-----------------------------------------------------------------------------------//
DirMonitor::DirMonitor(Path dir_path) : m_fd(NO_FILE),
                                        m_dir_path(dir_path),
                                        m_dispatcher(),
                                        is_running(false) {}

DirMonitor::~DirMonitor()
{
    is_running = false;
    if (NO_FILE < m_fd)
    {
        close(m_fd);
    }
}

void DirMonitor::AddSubscriber(CallBackBaseType *callback)
{
    if (nullptr == callback)
    {
        return;
    }

    m_dispatcher.Subscribe(callback);
}

void DirMonitor::Run()
{
    int watch_desc = init_monitoring();
    if (NO_FILE == watch_desc)
    {
        close(m_fd);
    }

    char buff[BUFSIZ] = {0};
    
    is_running = true;
    while (is_running)
    {
        ssize_t num_of_bytes_read = read(m_fd, buff, BUFSIZ);
        if (-1 == num_of_bytes_read)
        {
            return;
        }

        INotify_Event* event = {0};
        for (ssize_t i = 0; i < num_of_bytes_read; i += sizeof(struct inotify_event) + event->len)
        {
            event = reinterpret_cast<INotify_Event*>(&buff[i]);
            if (0 < event->len)
            {
                Key file_name(event->name);
                
                '/' != m_dir_path.back() ? m_dispatcher.NotifyAll(m_dir_path + '/' + file_name) 
                                         : m_dispatcher.NotifyAll(m_dir_path + file_name);
            }
            
        }
    }
}

//----------------------------------------------------------------------------------//
//################################# DLL LOADER #####################################//
//----------------------------------------------------------------------------------//

DllLoader::DllLoader() : m_callback(*this, &DllLoader::LoadNewSO, nullptr) {}

CallBackBaseType* DllLoader::GetCallBack()
{
    return &m_callback;
}

void DllLoader::LoadNewSO(const Path &so_name)
{
    if (so_name.empty())
    {
        return;
    }

    void* shared_obj = dlopen(so_name.c_str(), RTLD_NOW);
    if (NULL == shared_obj)
    {
        std::cerr << "failed to load library: " << dlerror() << std::endl;
        return;
    }
}

//----------------------------------------------------------------------------------------//
//################################# HELPER FUNCTIONS #####################################//
//----------------------------------------------------------------------------------------//

int DirMonitor::init_monitoring()
{
    m_fd = inotify_init();
    if (0 > m_fd)
    {
        return FAILURE;
    }

    int watch_desc = inotify_add_watch(m_fd, m_dir_path.c_str(), IN_CREATE 
                                                               | IN_CLOSE_WRITE
                                                               | IN_MOVED_TO);
    return watch_desc;
}

}