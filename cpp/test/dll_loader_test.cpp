#include <thread>
#include <chrono>

#include "dll_loader.hpp"

using namespace ilrd_178;

int main()
{
    Path path_to_monitor("./exercises/shared_objects_dll_loader");
    DirMonitor dm(path_to_monitor);
    DllLoader dll_loader;

    std::thread monitor([&dm]() {dm.Run();}); // &DirMonitor::Run, &dm, nullptr);
    monitor.detach();

    dm.AddSubscriber(dll_loader.GetCallBack());

    std::this_thread::sleep_for(std::chrono::seconds(35));

    return 0;
}