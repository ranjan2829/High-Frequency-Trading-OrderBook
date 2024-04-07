#pragma once
#include <list>
#include <exception
#include <format>
#include "OrderType.h"
#include "Side.h"
#include "Usings.h"
#include "Constants.h"

class Order{
public:
    Order(OrderType orderType,OrderId orderID,Side side,Price price,Quantity quantity)
         :orderType_{orderType}
         ,orderId_{orderId}
         ,side_{side}
         ,price_{price}
         ,initialQuantity_{quantity}
         ,remainingQuantity_{quantity}
    {}
    Order(OrderId orderId,Side side,Quantity quantity)
         :Order(OrderType::Market,orderId,side,Constants::InvalidPrice,quantity)
    {}
    OrderId GetOderId() const { return orderId_;}
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    OrderType getOrderType() const {return orderType_;}
    Quantity GetinitialQuantity() const {return initialQuantity_;}
    Quantity GetRemainingQuantity() const {return remainingQuantity_;}
    Quantity GetFilledQuantity() const {return GetinitialQuantity()-GetRemainingQuantity();}
    bool isFilled() const {return GetRemainingQuantity()==0;}
    void Fill(Quantity quantity){
        if{quantity > GetRemainingQuantity()}
    }

};