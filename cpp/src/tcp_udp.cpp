#include <iostream>     // cerr
#include <cstring>      // memset
#include <unistd.h>     // close
#include <netinet/in.h> // struct sockadd_in
#include <thread>       // thread
#include <arpa/inet.h>  // inet_pton

#include "tcp_udp.hpp"

namespace ilrd_178
{

//------------------------------------------------------------------------------//
//############################### SERVER TCP ###################################//
//------------------------------------------------------------------------------//

ServerTCP::ServerTCP(int port, int queue_size) : 
m_server_socket(socket(AF_INET, SOCK_STREAM, 0)),
m_client_socket(-1), 
m_queue_size(queue_size)
{
    if (0 > m_server_socket)
    {
        throw std::runtime_error("Server socket creation failed");
    }
    struct sockaddr_in server_addr{};
    std::memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (0 > bind(m_server_socket, 
                 reinterpret_cast<struct sockaddr*>(&server_addr), 
                 sizeof(server_addr)))
    {
        close(m_server_socket);
        throw std::runtime_error("Failed binding server socket");
    }

    if (0 > listen(m_server_socket, m_queue_size))
    {
        close(m_server_socket);
        throw std::runtime_error("Failed listening to server socket");
    }
}

ServerTCP::~ServerTCP()
{
    if (0 <= m_server_socket )
    {
        close(m_server_socket);
    }
    if (0 <= m_client_socket)
    {
        close(m_client_socket);
    }
}

ssize_t ServerTCP::Send(const char *data, size_t data_size)
{
    return send(m_client_socket, data, data_size, 0);
}

ssize_t ServerTCP::Receive(char *buffer, size_t data_size)
{
    return recv(m_client_socket, buffer, data_size, 0);
}

//------------------------------------------------------------------------------//
//############################### CLIENT TCP ###################################//
//------------------------------------------------------------------------------//

void ServerTCP::acception()
{ 
    struct sockaddr_in client_addr{};
    int addrlen = sizeof(client_addr);
    m_client_socket = accept(m_server_socket, 
                             reinterpret_cast<struct sockaddr*>(&client_addr), 
                             reinterpret_cast<socklen_t*>(&addrlen));
    if(0 > m_client_socket)
    {
        std::cerr << "failed accepting the socket" << std::endl;
    }
}

ClientTCP::ClientTCP(int port, const char* ip) : 
m_socket(socket(AF_INET, SOCK_STREAM, 0)) 
{
    if (0 > m_socket)
    {
        throw std::runtime_error("Client socket creation failed");
    }
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(struct sockaddr_in));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (0 > inet_pton(AF_INET, ip, &addr.sin_addr))
    {
        close(m_socket);
        throw std::runtime_error("Invalid IP address format");
    }

    if (0 > connect(m_socket, reinterpret_cast<struct sockaddr*>(&addr), sizeof(addr)))
    {
        close(m_socket);
        throw std::runtime_error("Failed connecting to server");
    }
}
ClientTCP::~ClientTCP()
{
    if (0 <= m_socket)
    {
        close(m_socket);
    }
}

ssize_t ClientTCP::Send(const char *data, size_t data_size)
{
    return send(m_socket, data, data_size, 0);
}

ssize_t ClientTCP::Receive(char *buffer, size_t data_size)
{
    return recv(m_socket, buffer, data_size, 0);
}

//-----------------------------------------------------------------------//
//############################### UDP ###################################//
//-----------------------------------------------------------------------//

SocketUDP::SocketUDP(int port) : m_socket(socket(AF_INET, SOCK_DGRAM, 0))
{
    if (0 > m_socket)
    {
        throw std::runtime_error("Server socket creation failed");
    }

    struct sockaddr_in addr{};
    std::memset(&addr, 0, sizeof(struct sockaddr_in));
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (0 > bind(m_socket, 
                 reinterpret_cast<struct sockaddr*>(&addr), 
                 sizeof(addr)))
    {
        close(m_socket);
        throw std::runtime_error("Failed binding server socket");
    }
}

SocketUDP::~SocketUDP()
{
    if (0 <= m_socket)
    {
        close(m_socket);
    }
}

ssize_t SocketUDP::SendTo(const char *data, size_t data_size, const char *dest_ip, int dest_port)
{
    struct sockaddr_in dest_addr;
    std::memset(&dest_addr, 0, sizeof(struct sockaddr_in));

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(dest_port);
    if (0 > inet_pton(AF_INET, dest_ip, &dest_addr.sin_addr))
    {
        close(m_socket);
        throw std::runtime_error("Invalid IP address format");
    }

    return sendto(m_socket, 
                  data, 
                  data_size, 
                  0, 
                  reinterpret_cast<struct sockaddr*>(&dest_addr), 
                  sizeof(dest_addr));
}

ssize_t SocketUDP::ReceiveFrom(char *buffer, size_t data_size, std::string &from_ip, int &from_port)
{
    struct sockaddr_in from_addr{};
    socklen_t addrlen = sizeof(from_addr);

    ssize_t tot_bytes_recv = recvfrom(m_socket, 
                                      buffer, 
                                      data_size,
                                      0,
                                      reinterpret_cast<struct sockaddr*>(&from_addr),
                                      &addrlen);

    if (tot_bytes_recv >= 0)
    {
        char ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &from_addr.sin_addr, ip_str, sizeof(ip_str));
        from_ip = ip_str;
        from_port = ntohs(from_addr.sin_port);
    }

    return tot_bytes_recv;
}

void SocketUDP::EnableBroadcast()
{
    int permit = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &permit, sizeof(permit)) < 0)
    {
        throw std::runtime_error("Failed to set SO_BROADCAST socket option");
    }
}

void SocketUDP::DisableBroadcast()
{
    int permit = 0;
    if (setsockopt(m_socket, SOL_SOCKET, SO_BROADCAST, &permit, sizeof(permit)) < 0)
    {
        throw std::runtime_error("Failed to set SO_BROADCAST socket option");
    }
}
}
