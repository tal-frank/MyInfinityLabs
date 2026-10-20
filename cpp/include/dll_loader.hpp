/**********************
* dll loader
* Author: Tal Frank
* Reviewer: Or Zellner
* Last update: 20/10/2026
**********************/

#ifndef ILRD_178_DLL_LOADER_DIR_MONITOR_HPP
#define ILRD_178_DLL_LOADER_DIR_MONITOR_HPP

#include "dispatcher.hpp" 

#include <sys/inotify.h> // inotify
#include <string>        // std::string
#include <cstdio>        // FILE

const int FAILURE = -1;
const int SUCCESS = 0;

namespace ilrd_178
{

using INotify_Event = struct inotify_event;
using Key = std::string;
using Path = std::string;
using CallBackBaseType = CallbackBase<Key>;

class DirMonitor
{    
public:
    explicit DirMonitor(Path dir_path);
    ~DirMonitor();
    
    void AddSubscriber(CallBackBaseType* callback);
    void Run();
    
private:
    int init_monitoring();

    int m_fd;
    const Path m_dir_path;
    Dispatcher<Key> m_dispatcher;
    bool is_running;
};

class DllLoader
{
public:
    explicit DllLoader();
    ~DllLoader() = default;

    CallBackBaseType* GetCallBack();

private:
    void LoadNewSO(const Path& so_name);

    CallBack<DllLoader, Key> m_callback;
};

} // namespace ilrd_178

#endif // ILRD_178_DLL_LOADER_DIR_MONITOR_HPP
