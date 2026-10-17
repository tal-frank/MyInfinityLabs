// #include "dispatcher.hpp"

// int main()
// {
//     return 0;
// }

#include <iostream>
#include <string>
#include <cassert>

#include "dispatcher.hpp" // Assuming your code is saved here

using namespace ilrd_178;

// Mock classes for testing
class DataModel
{
public:
    void OnDataChanged(const std::string& msg) {
        std::cout << "DataModel received message: " << msg << std::endl;
    }
};

class ViewWindow
{
public:
    ViewWindow(Dispatcher<std::string>& disp) : m_disp(disp), m_cb(nullptr) {}
    
    void Render(const std::string& msg) {
        std::cout << "ViewWindow rendering: " << msg << std::endl;
    }
    
    void StopAction() {
        std::cout << "ViewWindow stopped." << std::endl;
    }

    void RemoveSelfCallback(const std::string& msg) {
        std::cout << "ViewWindow removing its callback during broadcast!" << std::endl;
        if (m_cb) {
            m_disp.Unsubscribe(m_cb);
            delete m_cb;
            m_cb = nullptr;
        }
    }

    void AddOtherCallback(const std::string& msg) {
        std::cout << "ViewWindow adding a new observer during broadcast!" << std::endl;
        // Logic to add a new callback...
    }

    CallBack<ViewWindow, std::string>* m_cb;
    Dispatcher<std::string>& m_disp;
};

class ControlWindow
{
public:
    void HandleControl(const std::string& msg) {
        std::cout << "ControlWindow handling control: " << msg << std::endl;
    }
};

// --- Test Functions ---
void TestBroadcasts()
{
    std::cout << "\n--- Running Broadcast Tests ---\n";
    Dispatcher<std::string> dispatcher;
    
    DataModel model;
    ViewWindow view(dispatcher);
    ControlWindow control;

    CallBack<DataModel, std::string> cbModel(model, &DataModel::OnDataChanged);
    CallBack<ViewWindow, std::string> cbView(view, &ViewWindow::Render);
    CallBack<ControlWindow, std::string> cbControl(control, &ControlWindow::HandleControl);

    // 1. Broadcast to one observer
    dispatcher.Subscribe(&cbModel);
    dispatcher.NotifyAll("Event 1");

    // 2. Broadcast to two observers
    dispatcher.Subscribe(&cbView);
    dispatcher.NotifyAll("Event 2");

    // 3. Broadcast to three observers
    dispatcher.Subscribe(&cbControl);
    dispatcher.NotifyAll("Event 3");

    dispatcher.Unsubscribe(&cbModel);
    dispatcher.Unsubscribe(&cbView);
    dispatcher.Unsubscribe(&cbControl);
}

void TestModificationsDuringBroadcast()
{
    std::cout << "\n--- Running Modification During Broadcast Tests ---\n";
    Dispatcher<std::string> dispatcher;

    DataModel model;
    ViewWindow view(dispatcher);

    // Using a callback that removes itself during broadcast
    CallBack<ViewWindow, std::string> cbSelfRemove(view, &ViewWindow::RemoveSelfCallback);
    CallBack<DataModel, std::string> cbModel(model, &DataModel::OnDataChanged);

    dispatcher.Subscribe(&cbSelfRemove);
    dispatcher.Subscribe(&cbModel);

    // Should remove one observer during broadcast safely without crashing
    dispatcher.NotifyAll("Trigger Self Removal");
}

int main()
{
    TestBroadcasts();
    TestModificationsDuringBroadcast();
    std::cout << "\nAll tests executed!\n";
    return 0;
}