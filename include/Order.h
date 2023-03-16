#ifndef ORDER_H
#define ORDER_H

#include <string>

class Order
{
public:
    enum class Type
    {
        BUY,
        SELL
    };

    Order(int id, Type type, double price, int quantity);

    int getId() const;
    Type getType() const;
    double getPrice() const;
    int getQuantity() const;
    void setQuantity(int newQuantity);

    std::string typeToString() const;
    void reduceQuantityById(int amount);
    void reduceQuantity(int quantity);
    void updateOrderQuantityById(int id, int newQuantity);
    void removeOrderById(int id);

private:
    int id;
    Type type;
    double price;
    int quantity;
};

#endif // ORDER_H
