#ifndef TCP_UDP
#define TCP_UDP

#include <sys/socket.h> // socket

namespace ilrd_178
{
enum Protocol
{
    TCP,
    UDP
};

class ServerTCP
{
public:
    ServerTCP(int port, int queue_size);
    ~ServerTCP();

    ssize_t Send(const char* data, size_t data_size);
    ssize_t Receive(char* buffer, size_t data_size);

    void acception();
private:
    int m_server_socket;
    int m_client_socket;
    int m_queue_size;
};

class ClientTCP
{
public:
    ClientTCP(int port, const char* ip);
    ~ClientTCP();

    ssize_t Send(const char* data, size_t data_size);
    ssize_t Receive(char* buffer, size_t data_size);
private:
    int m_socket;
};

class SocketUDP
{
public:
    SocketUDP(int port = 0);
    ~SocketUDP();

    ssize_t SendTo(const char* data, size_t data_size, const char* dest_ip, int dest_port);
    ssize_t ReceiveFrom(char* buffer, size_t data_size, std::string& from_ip, int& from_port);

    void EnableBroadcast();
    void DisableBroadcast();
private:
    int m_socket;
};
}

#endif