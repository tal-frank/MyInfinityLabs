#include <vector>
#include <string>
#include <iostream>

const std::string RED   = "\033[31m";
const std::string RESET = "\033[0m";

class Notification
{
public:
    virtual ~Notification() = default;
    virtual void send() const = 0;
};

class EmailNotification : public Notification
{
public:
    void send() const override;
};

class SMSNotification : public Notification
{
public:
    void send() const override;
};

class PushNotification : public Notification
{
public:
    void send() const override;
};

void EmailNotification::send() const
{
    std::cout << "sending" << RED << " EMAIL " << RESET << "notification\n";
}

void SMSNotification::send() const
{
    std::cout << "sending" << RED << " SMS " << RESET << "notification\n";
}

void PushNotification::send() const
{
    std::cout << "sending" << RED << " PUSH " << RESET << "notification\n";
}

void sendAll(const std::vector<Notification*>& notifications)
{
    for (const Notification* notification : notifications)
    {
        if (nullptr != notification)
        {
            notification->send();
        }
    }    
}

int main()
{
    std::vector<Notification*> notifications;
    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    notifications.push_back(&email);
    notifications.push_back(&sms);
    notifications.push_back(&push);

    sendAll(notifications);
    return 0;
}
