#include <iostream>
#include <winsock2.h>
#include "..\include\OrderBook.h"
#include <sstream>
#include "..\include\MatchingEngine.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, recv_size;
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Bind the socket to a local address and port
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(9000);

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(s, SOMAXCONN);

    std::cout << "Waiting for incoming connections..." << std::endl;

    // Accept incoming connections
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(s, (struct sockaddr *)&client, &c)) != INVALID_SOCKET)
    {
        std::cout << "Connection accepted" << std::endl;
        OrderBook orderBook;
        int orderId = 1;
        // Receive data from the client
        while ((recv_size = recv(new_socket, buffer, sizeof(buffer), 0)) > 0)
        {
            std::istringstream ss(buffer);
            std::cout << buffer;
            std::string orderTypeStr;
            double price;
            unsigned int quantity;
            ss >> orderTypeStr >> price >> quantity;

            Order::Type orderType = orderTypeStr == "Buy" ? Order::Type::BUY : Order::Type::SELL;
            // Use a random number for the ID, you can improve this by maintaining an ID counter
            orderId++;
            Order order(orderId, orderType, price, quantity);
            // orderBook.addOrder(order);
            // orderBook.sortOrders();
            // orderBook.printOrders();
            orderBook.addOrder(order);
            orderBook.groupOrdersByPrice();
            std::cout << "Before matched ";
            orderBook.printOrders();

            MatchingEngine matchingEngine(orderBook);
            matchingEngine.matchOrders();

            // Print matched trades
            std::cout << "Trade ";
            matchingEngine.printTrades();

            // Print the remaining orders in the order book
            std::cout << "After matched ";
            orderBook.printOrders();

            // Clear the buffer for the next message
            memset(buffer, 0, sizeof(buffer));
        }

        if (recv_size == SOCKET_ERROR)
        {
            std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
        }

        // Close the connection
        closesocket(new_socket);
    }

    if (new_socket == INVALID_SOCKET)
    {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Cleanup Winsock
    WSACleanup();

    return 0;
}
