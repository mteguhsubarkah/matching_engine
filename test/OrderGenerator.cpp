#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include "..\include\Order.h"
#include <random>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        cerr << "Error initializing Winsock" << endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Change this to the IP address of the server you want to connect to
    server.sin_family = AF_INET;
    server.sin_port = htons(9000); // Change this to the port number of the server you want to connect to

    if (connect(sock, (sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        cerr << "Error connecting to server" << endl;
        return 1;
    }

    Order::Type currentOrderType = Order::Type::BUY;
    int orderId = 1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> float_dist(100, 500);
    std::uniform_int_distribution<int> int_dist(10, 100);
    while (true)
    {

        float random_float = float_dist(gen);
        int random_int = int_dist(gen);
        // Create a new order
        Order order(orderId++, currentOrderType, random_float, random_int);

        // Convert the order to a string
        string orderStr = order.typeToString() + " " + to_string(order.getPrice()) + " " + to_string(order.getQuantity()) + "\n";
        orderStr += '\0';
        int send_result = send(sock, orderStr.c_str(), orderStr.length(), 0);
        // std::cout << send_result;

        if (send_result == SOCKET_ERROR)
        {
            cerr << "Error sending order: " << WSAGetLastError() << endl;
            return 1;
        }
        std::cout << orderStr;
        // Send the order to the server
        if (send(sock, orderStr.c_str(), orderStr.length() + 1, 0) == SOCKET_ERROR)
        {
            cerr << "Error sending order. Error code: " << WSAGetLastError() << endl;
            return 1;
        }

        // Pause for 0.1 seconds
        Sleep(0.1);

        // Switch the order type for the next iteration
        currentOrderType = currentOrderType == Order::Type::BUY ? Order::Type::SELL : Order::Type::BUY;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
