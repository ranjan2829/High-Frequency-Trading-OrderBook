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
};