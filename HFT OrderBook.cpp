#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>
#include <tuple>
#include <format>
enum class OrderType{
    GoodTillCancel,
    FillAndKill
};

enum class Side{
    Buy,
    Sell
};
using Price =std::int32_t;
using Quantity =std::uint32_t;
using OrderId=std::uint64_t;
struct LevelInfo{
    Price price_;
    Quantity quantity_;
};
using LevelInfos=std::vector<LevelInfo>;
class OrderBookLevelInfos{
    public:
    OrderBookLevelInfos(const LevelInfos& bids,const LevelInfos& ask)
         : bids_{bids}
         , asks_{ asks }
    {}
    const LevelInfos& GetBids() const {return bids_;}
    const LevelInfos& GetBids() const {return asks_;}
    private:
    LevelInfos bids_;
    LevelInfos asks_;



}
class Order{
    public :
    Order(OrderType orderType,OrderID orderId , Side side,Price price,Quantity quantity){
        :orderType_{orderType}
        ,orderId_{OrderId}
        ,side_{side}
        ,price_{price}
        ,intialQuantity_{quantity}
        ,remainingQuantity{quantity}
    {}
    OrderId GetOrderID() const {return orderId_;}
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    OrderType GetOrderType() const {return orderType_;}
    Quantity GetInitialQuantity() const {return initialQuantity_;}
    Quantity GetRemainingQuantity() const {return remainingQuantity_;}
    Quantity GetFilledQuantity() const {return GetInitialQuantity()-GetRemainingQuantity();}
    void

    }
}


int main(){


    return 0;

}