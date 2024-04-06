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
    void Fill(Quantity quantity){
        if(quantity >GetRemainingQuantity()){
            throw std::logic_error(std::format("Orddr ({}) cannot be filled for more than it's remaining quantity . ",GetOrderID()));
        }
        remainingQuantity -=quantity;
    }
    private:
    OrderType orderType_;;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;

    };
};
using OrderPointer =std::shared_ptr<Order>;
using OrderPointers=std::list<OrderPointer>;
class OrderModify{
    public :
    OrderModify(OrderId orderID,Side side,Price price,Quantity quantity)
            :orderId_{orderId}
            ,price_{price}
            ,side_{side}
            ,quantity_ {quantity}

    {}
    OrderId GetOrderId() const { return orderId_;}
    Price GetPrice() const {return price_;}
    Side GetSide() const {return side_;}
    Quantity GetQuantity() const {return quantity_;}

    OrderPointer ToOrderPointer(OrderType type) const{
        return std::make_shared<Order>(type,GetOrderId(),GetSide(),GetPrice(),GetQuantity());
    }
    private:
    OrderId orderId_;
    Price price_;
    Side side_;
    Quantity quantity_;

}
struct TradeInfo{
    OrderId orderId_;
    Price price_;
    Quantity quantity_;

};

class Trade{
    public: 
    Trade(const TradeInfo& bidTrade,const Tradeinfo& askTrade)
         : bidTrade_{ bidTrade}
         ,askTrade_{askTrade}
    {}
    const TradeInfo& GetBidTrade() const {return bidTrade_;}
    const TradeInfo& GetAskTrade() const {return askTrade_;}

    private:
    TradeInfo bidTrade_;
    TradeInfo askTrade_;

          
};
using Trades =std::vector<Trade>;
class OrderBook{
private:
    struct OrderEntry{
        OrderPointer order_{nullptr};
        OrderPointers ::iterator location_;

    };
    std::map<Price,OrderPointers ,std::greater<Price>> bids_;
    std::map<Price,OrderPointers ,std::less<Price>> asks_;
    std::unordered_map<OrderID,OrderEntry> orders_;
    bool CanMatch(Side side, Price price) const {
        if(side==Side::Buy){
            if(asks_.empty()){
                return false;
                const auto& [bestAsk,_]=*asks_.begin();
                return price>=bestAsk;

            }
        }
    }

};




int main(){


    return 0;

}