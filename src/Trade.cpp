#include "..\include\Trade.h"

Trade::Trade(int buy_order_id, int sell_order_id, double done_price, int done_quantity)
    : buy_order_id(buy_order_id), sell_order_id(sell_order_id), done_price(done_price), done_quantity(done_quantity) {}

int Trade::getBuyOrderId() const
{
    return buy_order_id;
}

int Trade::getSellOrderId() const
{
    return sell_order_id;
}

double Trade::getDonePrice() const
{
    return done_price;
}

int Trade::getDoneQuantity() const
{
    return done_quantity;
}

void Trade::printTrade() const
{

    std::cout << "Trade: Buy Order ID: " << buy_order_id
              << ", Sell Order ID: " << sell_order_id
              << ", Done Price: " << done_price
              << ", Done Quantity: " << done_quantity;
}