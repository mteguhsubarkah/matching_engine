#include "..\include\MatchingEngine.h"
#include <algorithm>
MatchingEngine::MatchingEngine(OrderBook &orderBook) : orderBook(orderBook) {}

void MatchingEngine::matchOrders()
{
    orderBook.sortOrders();

    while (true)
    {
        try
        {
            Order bestBid = orderBook.getBestBid();
            Order bestSell = orderBook.getBestSell();

            // Check if best bid price is greater or equal to best sell price
            if (bestBid.getPrice() >= bestSell.getPrice())
            {
                // Match the orders
                int doneQuantity = std::min(bestBid.getQuantity(), bestSell.getQuantity());
                double donePrice = bestSell.getPrice();

                // Create trade and add to the list of trades
                Trade trade(bestBid.getId(), bestSell.getId(), donePrice, doneQuantity);
                trades.push_back(trade);

                // Update orders
                bestBid.reduceQuantityById(doneQuantity);
                bestSell.reduceQuantityById(doneQuantity);

                if (bestBid.getQuantity() == 0)
                {
                    orderBook.removeOrderById(bestBid.getId());
                }

                if (bestSell.getQuantity() == 0)
                {
                    orderBook.removeOrderById(bestSell.getId());
                }
            }
            else
            {
                break; // No more matches possible
            }
        }
        catch (const std::runtime_error &e)
        {
            break; // No matching orders found
        }
    }
}

void MatchingEngine::printTrades() const
{
    std::cout << "\nMatched Trades:\n";
    for (const auto &trade : trades)
    {
        trade.printTrade();
    }
}