#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include "tcp_udp.hpp"

const int TEST_PORT = 12345;
const int QUEUE_SIZE = 5;

void RunServer()
{
    try
    {
        ilrd_178::ServerTCP server(TEST_PORT, QUEUE_SIZE);
        std::cout << "[Server] Waiting for client connection...\n";
        server.acception();
        std::cout << "[Server] Client connected!\n";

        // 1. Server sends "ping"
        const char* msg_out = "ping";
        std::cout << "[Server] Sending: \"" << msg_out << "\"\n";
        server.Send(msg_out, std::strlen(msg_out));

        // 2. Server waits for "pong" response
        char buffer[256] = {0};
        ssize_t bytes_received = server.Receive(buffer, sizeof(buffer) - 1);
        if (bytes_received > 0)
        {
            std::cout << "[Server] Received: \"" << buffer << "\"\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Server Error] " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "=== Starting Ping-Pong TCP Test ===\n\n";

    try
    {
        // Start server on a background thread
        std::thread server_thread(RunServer);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Brief pause for bind

        // Client connects
        std::cout << "[Client] Connecting to server...\n";
        ilrd_178::ClientTCP client(TEST_PORT, "127.0.0.1");
        std::cout << "[Client] Connected!\n";

        // 1. Client receives "ping" from server
        char buffer[256] = {0};
        ssize_t bytes_received = client.Receive(buffer, sizeof(buffer) - 1);
        if (bytes_received > 0)
        {
            std::cout << "[Client] Received: \"" << buffer << "\"\n";
        }

        // 2. Client sends "pong" back
        const char* msg_out = "pong";
        std::cout << "[Client] Sending: \"" << msg_out << "\"\n";
        client.Send(msg_out, std::strlen(msg_out));

        // Wait for server thread to finish
        if (server_thread.joinable())
        {
            server_thread.join();
        }

        std::cout << "\n=== TCP Ping-Pong Test Completed Successfully! ===\n\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "\n[Test Failure] " << e.what() << std::endl;
        return 1;
    }


    std::cout << "=== Starting UDP Broadcast & Ping-Pong Test ===\n";

    try
    {
        // 1. Create two UDP nodes bound to different ports
        ilrd_178::SocketUDP node_a(8001); // Node A listens on port 8001
        ilrd_178::SocketUDP node_b(8002); // Node B listens on port 8002

        // Enable broadcasting on Node A
        node_a.EnableBroadcast();

        // 2. Test Unicast Ping-Pong (Node A sends "ping" to Node B)
        const char* ping_msg = "ping";
        std::cout << "[Node A] Sending ping to Node B (Port 8002)...\n";
        node_a.SendTo(ping_msg, std::strlen(ping_msg), "127.0.0.1", 8002);

        // Node B receives ping
        char buffer[256] = {0};
        std::string sender_ip;
        int sender_port = 0;

        node_b.ReceiveFrom(buffer, sizeof(buffer) - 1, sender_ip, sender_port);
        std::cout << "[Node B] Received \"" << buffer << "\" from " << sender_ip << ":" << sender_port << "\n";

        // Node B responds with "pong" back to Node A
        const char* pong_msg = "pong";
        std::cout << "[Node B] Sending pong back to Node A (Port 8001)...\n";
        node_b.SendTo(pong_msg, std::strlen(pong_msg), sender_ip.c_str(), sender_port);

        // Node A receives pong
        std::memset(buffer, 0, sizeof(buffer));
        node_a.ReceiveFrom(buffer, sizeof(buffer) - 1, sender_ip, sender_port);
        std::cout << "[Node A] Received \"" << buffer << "\" from " << sender_ip << ":" << sender_port << "\n";


        // 3. Test Broadcast (Node A broadcasts to the local subnet broadcast address)
        const char* broadcast_msg = "Hello Network!";
        std::cout << "\n[Node A] Broadcasting message to 255.255.255.255:8002...\n";
        node_a.SendTo(broadcast_msg, std::strlen(broadcast_msg), "255.255.255.255", 8002);

        // Node B receives the broadcast
        std::memset(buffer, 0, sizeof(buffer));
        node_b.ReceiveFrom(buffer, sizeof(buffer) - 1, sender_ip, sender_port);
        std::cout << "[Node B] Received Broadcast: \"" << buffer << "\" from " << sender_ip << ":" << sender_port << "\n";

        std::cout << "\n=== UDP Test Passed Successfully! ===\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "[UDP Test Error] " << e.what() << std::endl;
        return 1;
    }


    return 0;
}