#include "..\include\Order.h"
#include <iostream>

Order::Order(int id, Type type, double price, int quantity)
    : id(id), type(type), price(price), quantity(quantity) {}

int Order::getId() const
{
    return id;
}

Order::Type Order::getType() const
{
    return type;
}

double Order::getPrice() const
{
    return price;
}

int Order::getQuantity() const
{
    return quantity;
}

std::string Order::typeToString() const
{
    return type == Type::BUY ? "Buy" : "Sell";
}

void Order::reduceQuantityById(int amount)
{
    if (amount > 0 && amount <= quantity)
    {
        quantity -= amount;
        setQuantity(quantity);
    }
    else
    {
        throw std::invalid_argument("Invalid amount for reducing quantity");
    }
}

void Order::setQuantity(int newQuantity)
{
    if (newQuantity >= 0)
    {
        quantity = newQuantity;
    }
    else
    {
        throw std::invalid_argument("Invalid quantity: Quantity must be non-negative");
    }
}