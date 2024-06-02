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
        {
            enum class Action{
                ADD,
                Remove,
                MATCH,

            };
        }
    };
    std::unordered_map<Price,LevelData> data_;
    std::map<Price,OrderPointers,std::greater<Price>> bids_;
    std::map<Price,OrderPointers ,std::less<Price>> asks_;
    std::unordered_map<OrderId,OrderEntry> orders_;
    mutable std::mutex ordersMutex_;
    std::thread ordersPruneThread_;
    std::condition_variable shutdownConditionVariable_;
    std::atomic<bool> shutdown_{false};



};