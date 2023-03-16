#ifndef TRADE_H
#define TRADE_H

#include <iostream>

class Trade
{
public:
    Trade(int buy_order_id, int sell_order_id, double done_price, int done_quantity);

    int getBuyOrderId() const;
    int getSellOrderId() const;
    double getDonePrice() const;
    int getDoneQuantity() const;
    std::string getOrderStatus() const;
    void printTrade() const;

private:
    int buy_order_id;
    int sell_order_id;
    double done_price;
    int done_quantity;
    std::string status_order;
};

#endif // TRADE_H