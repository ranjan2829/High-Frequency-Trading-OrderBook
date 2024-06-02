//
// Created by Ranjan shahaji shitole on 02/06/24.
//
#include <map>
#include <unordered_map>
#include <thread>
#include <condition_variable
#include <mutex>

#include "Usings.h"
#include "ORder.h"
#include "OrderModify.h"
#include "OrderbookLevelInfos.h"
#include "Trade.h"

class OrderBook{
private:
    struct OrderEntry{
        OrderPointer order_{nullptr};
        OrderPointers ::iterator location_;

    };
    struct LevelData{
        Quantity quantity_{};
        Quantity count_{};

        enum class Action{
                ADD,
                Remove,
                MATCH,

            };
    };

    std::unordered_map<Price,LevelData> data_;
    std::map<Price,OrderPointers,std::greater<Price>> bids_;
    std::map<Price,OrderPointers ,std::less<Price>> asks_;
    std::unordered_map<OrderId,OrderEntry> orders_;
    mutable std::mutex ordersMutex_;
    std::thread ordersPruneThread_;
    std::condition_variable shutdownConditionVariable_;
    std::atomic<bool> shutdown_{false};


    void PruneGoodForDaysOrders();
    void CancelORders(OrderIds orderIds);
    void CancelOrderInternal( OrderId orderId);
    void OnOrderCancelled( OrderPointer order);
    void onOrderAdded(OrderPointer order);

    void onOrderMatched(Price price,Quantity quantity,bool isFullFilled);
    void UpdateLevelData(Price price, Quantity quantity,LevelData::Action action );

    bool CanFullyFill(SIde side,Price price ,Quantity quantity) const;
    bool CanMatch(Side side,Price price ) const;
    Trades MatchOrders();
public:
    OrderBook();
    OrderBook(const OrderBook&) =delete;
    void operator =(const OrderBook&)=delete;
    OrderBook(OrderBook&&)=delete;
    void operator=(Orderbook&&)=delete;
    ~OrderBook();





};