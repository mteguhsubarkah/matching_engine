MATCHING ENGINE

This is a simple example of mathcing engine that able to matching order transaction based on order queue that represent in orderbook. The engine are catch orders from client via TCP/IP communication which later will separated of the type (buy and sell) and ordered as well that generate order book. This engine are limited to filled and partial filled status.

The pre-requisites :

- MinGw
- C++11 or higher

This project consist of .\includes , .\src and .\test folder that represent data structure, implementation, and testing respectively.

- Order class represent in Order.h and Order.cpp. This class will struct a data of order and implement some method to get and set order value and also update the order after its matched
- Trade class represent in Trade.h and Trade.cpp. This class will struct a data of a trade thats generated from a matched order and implement some method to get and set trade value.
- OrderBook class represent in OrderBook.h and OrderBook.cpp. This class will generate an order book from all of incoming order that received from TCP/IP connection.
- MatchingEngine class is represent in MatchingEngine.h and MatchingEngine.cpp. This class will handle a matching algroithm of all incoming order.
- main.cpp is main program to receive order from client, generate to an orderbook , and matching the order.
- DataGenerator.cpp is an order generator which sent to server side that later will be matched.

To run :

- Use this command : `main.exe` to run the main program (main.cpp)
- Use this command : `ordergenerator.exe` to generate order and send to main (DataGenerator.cpp)
