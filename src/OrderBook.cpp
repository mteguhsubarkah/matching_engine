#include "..\include\OrderBook.h"
#include <iostream>
#include <map>

#include <algorithm>

void OrderBook::addOrder(const Order &order)
{
    orders.push_back(order);
}

void OrderBook::printOrders() const
{
    std::cout << "Orders:\n";
    for (const auto &order : orders)
    {
        std::cout << "ID: " << order.getId()
                  << ", Type: " << order.typeToString()
                  << ", Price: " << order.getPrice()
                  << ", Quantity: " << order.getQuantity() << '\n';
    }
}

// Add sortBuyOrdersDescending method
void OrderBook::sortBuyOrdersDescending()
{
    std::sort(orders.begin(), orders.end(), [](const Order &a, const Order &b)
              {
        if (a.getType() == Order::Type::BUY && b.getType() == Order::Type::BUY)
            return b.getPrice() < a.getPrice();
        return false; });
}

void OrderBook::sortSellOrdersAscending()
{
    std::sort(orders.begin(), orders.end(), [](const Order &a, const Order &b)
              {
        if (a.getType() == Order::Type::SELL && b.getType() == Order::Type::SELL)
            return a.getPrice() < b.getPrice();
        return false; });
}

Order OrderBook::getBestBid() const
{
    for (const auto &order : orders)
    {
        if (order.getType() == Order::Type::BUY)
        {
            return order;
        }
    }
    throw std::runtime_error("No best bid found.");
}

Order OrderBook::getBestSell() const
{
    for (const auto &order : orders)
    {
        if (order.getType() == Order::Type::SELL)
        {
            return order;
        }
    }
    throw std::runtime_error("No best sell found.");
}

void OrderBook::removeOrderById(int id)
{
    auto it = std::remove_if(orders.begin(), orders.end(),
                             [id](const Order &order)
                             { return order.getId() == id; });

    if (it != orders.end())
    {
        orders.erase(it, orders.end());
    }
    else
    {
        std::cerr << "Error: Order ID not found!";
    }
}

void OrderBook::sortOrders()
{
    sortBuyOrdersDescending();
    sortSellOrdersAscending();
}

void OrderBook::groupOrdersByPrice()
{
    std::map<double, int> buyOrdersMap;
    std::map<double, int> sellOrdersMap;

    for (const auto &order : orders)
    {
        if (order.getType() == Order::Type::BUY)
        {
            buyOrdersMap[order.getPrice()] += order.getQuantity();
        }
        else
        {
            sellOrdersMap[order.getPrice()] += order.getQuantity();
        }
    }

    orders.clear();

    for (const auto &pair : buyOrdersMap)
    {
        int orderId = rand() % 10000 + 1; // You can improve this by maintaining an ID counter
        Order buyOrder(orderId, Order::Type::BUY, pair.first, pair.second);
        orders.push_back(buyOrder);
    }

    for (const auto &pair : sellOrdersMap)
    {
        int orderId = rand() % 10000 + 1; // You can improve this by maintaining an ID counter
        Order sellOrder(orderId, Order::Type::SELL, pair.first, pair.second);
        orders.push_back(sellOrder);
    }

    sortOrders();
}
