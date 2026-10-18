// WS: 
// Author: 
// Reviewer: 
// Last Changed: 

#ifndef ILRD_178_DLL_LOADER_DIR_MONITOR_HPP
#define ILRD_178_DLL_LOADER_DIR_MONITOR_HPP

// ******************************************************* personal Libraries */

#include <unistd.h>         // read
#include <cstdint>          // uint32_t
#include <sys/inotify.h>    // inotify
#include <string>           // string

// ******************************************************* personal Libraries */

#include "temp_dispatcher.hpp"  // CallBack

namespace ilrd_178
{

// ******************************************************** struct DllMessage */

struct DllMessage
{
public:
    explicit DllMessage(uint32_t event_mask, std::string file_path)
                                                : m_event_mask(event_mask),
                                                  m_file_path(file_path) { }

    uint32_t m_event_mask;
    std::string m_file_path;
};

// ******************************************************* using declerations */

using INotify_Event = struct inotify_event;
using path = std::string;
using callback = CallbackBase<DllMessage>;

// ********************************************************* class DirMonitor */

class DirMonitor
{
static const uint32_t FLAGS = IN_CREATE | IN_DELETE | IN_MOVE | IN_MODIFY;

public:
    explicit DirMonitor(path dir_path);
    DirMonitor(const DirMonitor& other) = delete;
    DirMonitor& operator=(const DirMonitor& other) = delete;
    ~DirMonitor();

    void AddSubscriber(callback* callback);
    void Run();

    void RemoveSubscriber(callback* callback); // optional

private:
    static thread_local DirMonitor* th_param;

    static int InitNotify();
    void ThreadRoutine();

    path m_path;
    int m_events_q;
    int m_watch_id;
    bool is_running;
    Dispatcher<DllMessage> m_dispatcher;

}; // class DirMonitor

class DllLoader
{

public:
    void EventHandler(const DllMessage& message);

private:
    bool IsSharedObject(path& file_path);
    void LoadNewSO(const path& so_name);
    void UnLoadSO(const path& so_name); // optional
    void ReLoadSO(const path& so_name); // optional

}; // class DllLoader

}// namespace ilrd_178


#endif // End of ILRD_178_DLL_LOADER_DIR_MONITOR_HPP
