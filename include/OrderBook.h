#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <vector>
#include "Order.h"

class OrderBook
{
public:
    void addOrder(const Order &order);
    void printOrders() const;
    void sortBuyOrdersDescending();
    void sortSellOrdersAscending();
    void sortOrders();
    Order getBestBid() const;
    Order getBestSell() const;
    void removeOrderById(int id);
    void groupOrdersByPrice();

private:
    std::vector<Order> orders;
};

#endif // ORDER_BOOK_H