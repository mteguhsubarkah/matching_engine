#ifndef MATCHING_ENGINE_H
#define MATCHING_ENGINE_H

#include <iostream>
#include <vector>
#include "OrderBook.h"
#include "Trade.h"

class MatchingEngine
{
public:
    MatchingEngine(OrderBook &orderBook);

    void matchOrders();
    void printTrades() const;

private:
    OrderBook &orderBook;
    std::vector<Trade> trades;
};

#endif // MATCHING_ENGINE_H