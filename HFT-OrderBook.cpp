 #include <algorithm>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream> // Include the <sstream> header for std::ostringstream
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <vector>
#include "OrderBook.h"
#include <ctime>
#include <numeric>


void OrderBook::PruneGoodForDaysOrders(){
    using namespace std:: chrono;
    const auto end=hours(16);

    while(true){
        const auto now=system_clock::now();
        const auto now_c=system_clock::to_time_t(now);

        std::tm now_parts;
        localtime_s(&now_parts,&now_c);
        if(now_parts.tm_hour>=end.count()){
            now_parts.tm_mday+=1;
        }
        now_parts.tm_hour=end.count();
        now_parts.tm_min=0;
        now_parts.tm_sec=0;

        auto next=system_clock::from_time_t(mktime(&now_parts));
        auto till =next-now+milliseconds (100);

        {
            std::unique_lock orderLocks{ordersMutex_};
            if(shutdown_.load((std::memory_order_acquire)||shutdownConditionVariable_.wait_for(orderLocks,till)==std::cv_status::no_timeout)){
                return;
            }



        }
        OrderIds orderIds;
        {
            std::scoped_lock ordersLock{ordersMutex_};
            for (const auto& [_,entry]:orders_){
                const auto& [order,_]=entry;
                if(order->GetOrderType()!=OrderType::GoodForDay){
                    continue;
                }
                orderIds.push_back(order->GetOrderId());

            }

        }

       CancelOrder((orderIds);


    }

}
void OrderBook::CancelOrders(OrderIds orderIds) {
    std::scoped_lock ordersLock{orderMutex_};
    for (const auto& orderID:orderIds){
        CancelOrderInternal(orderID);
    }
}
void OrderBook::CancelOrderInternal(OrderId orderId) {
    if (!orders_.contains(orderId)){
        return;
    }
    const auto& [order,iterator]=orders_.at(orderId);
    orders_.erase(orderId);
    if(order->GetSide()==Side::Sell){
        auto price=order->GetPrice();
        auto& orders=asks_.at(price);
        orders.erase(iterator);
        if(orders.empty()){
            asks_.erase(price);
        }
        else{
            auto price =order->GetPrice();
            auto& orders=bids_.at(price);
            orders.erase(iterator);
            if(orders.empty()){
                bids_.erase(price);

            }
        }
    }
    onOrderCancelled(order);

}
void OrderBook::onOrderCancelled(OrderPointer order) {
    UpdateLevelData(order->GetPrice(), order->GetRemainingQuantity(), LevelData::Action::Remove);
}
void


Trades:: OrderBook::AddOrder(OrderPointer order){
    std::scoped_lock ordersLock{ordersMutex_};
    if(orders_.contains(order->GetOrderId())){
        return {};
    }
    if(order->GetOrderType()==OrderType::Market){
        if
    }
}

enum class OrderType { GoodTillCancel, FillAndKill };

enum class Side { Buy, Sell };

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;

struct LevelInfo {
  Price price_;
  Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderBookLevelInfos {
public:
  OrderBookLevelInfos(const LevelInfos &bids, const LevelInfos &asks)
      : bids_{bids}, asks_{asks} {}

  const LevelInfos &GetBids() const { return bids_; }
  const LevelInfos &GetAsks() const { return asks_; }

private:
  LevelInfos bids_;
  LevelInfos asks_;
};

class Order {
public:
  Order(OrderType orderType, OrderId orderId, Side side, Price price,
        Quantity quantity)
      : orderType_{orderType}, orderId_{orderId}, side_{side}, price_{price},
        initialQuantity_{quantity}, remainingQuantity_{quantity} {}

  OrderId GetOrderID() const { return orderId_; }
  Side GetSide() const { return side_; }
  Price GetPrice() const { return price_; }
  OrderType GetOrderType() const { return orderType_; }
  Quantity GetInitialQuantity() const { return initialQuantity_; }
  Quantity GetRemainingQuantity() const { return remainingQuantity_; }
  Quantity GetFilledQuantity() const {
    return GetInitialQuantity() - GetRemainingQuantity();
  }

  void Fill(Quantity quantity) {
    if (quantity > GetRemainingQuantity()) {
      std::ostringstream oss; // Use std::ostringstream for string formatting
      oss << "Order (" << GetOrderID()
          << ") cannot be filled for more than its remaining quantity.";
      throw std::logic_error(
          oss.str()); // Get the formatted string using oss.str()
    }
    remainingQuantity_ -= quantity;
  }

private:
  OrderType orderType_;
  OrderId orderId_;
  Side side_;
  Price price_;
  Quantity initialQuantity_;
  Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;



struct TradeInfo {
  OrderId orderId_;
  Price price_;
  Quantity quantity_;
};

class Trade {
public:
  Trade(const TradeInfo &bidTrade, const TradeInfo &askTrade)
      : bidTrade_{bidTrade}, askTrade_{askTrade} {}

  const TradeInfo &GetBidTrade() const { return bidTrade_; }
  const TradeInfo &GetAskTrade() const { return askTrade_; }

private:
  TradeInfo bidTrade_;
  TradeInfo askTrade_;
};

using Trades = std::vector<Trade>;

class OrderBook {
private:
  struct OrderEntry {
    OrderPointer order_{nullptr};
    OrderPointers::iterator location_;
  };

  std::map<Price, OrderPointers, std::greater<Price>> bids_;
  std::map<Price, OrderPointers, std::less<Price>> asks_;
  std::unordered_map<OrderId, OrderEntry> orders_;

  bool CanMatch(Side side, Price price) const {
    if (side == Side::Buy) {
      if (asks_.empty()) {
        return false;
      }
      const auto &[bestAsk, _] = *asks_.begin();
      return price >= bestAsk;
    } else {
      if (bids_.empty()) {
        return false;
      }
      const auto &[bestBid, _] = *bids_.begin();
      return price <= bestBid;
    }
  }

  Trades MatchOrders() {
    Trades trades;
    trades.reserve(orders_.size());

    while (true) {
      if (bids_.empty() || asks_.empty()) {
        break;
      }

      auto &[bidPrice, bids] = *bids_.begin();
      auto &[askPrice, asks] = *asks_.begin();

      if (bidPrice < askPrice) {
        break;
      }

      while (!bids.empty() && !asks.empty()) {
        auto &bid = bids.front();
        auto &ask = asks.front();
        Quantity quantity =
            std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());
        bid->Fill(quantity);
        ask->Fill(quantity);

        if (bid->GetRemainingQuantity() == 0) {
          bids.pop_front();
          orders_.erase(bid->GetOrderID());
        }
        if (ask->GetRemainingQuantity() == 0) {
          asks.pop_front();
          orders_.erase(ask->GetOrderID());
        }

        if (bids.empty()) {
          bids_.erase(bidPrice);
        }
        if (asks.empty()) {
          asks_.erase(askPrice);
        }

        trades.push_back(
            Trade{TradeInfo{bid->GetOrderID(), bid->GetPrice(), quantity},
                  TradeInfo{ask->GetOrderID(), ask->GetPrice(), quantity}});
      }
    }

    if (!bids_.empty()) {
      auto &[_, bids] = *bids_.begin();
      auto &order = bids.front();
      if (order->GetOrderType() == OrderType::FillAndKill) {
        CancelOrder(order->GetOrderID());
      }
    }

    if (!asks_.empty()) {
      auto &[_, asks] = *asks_.begin();
      auto &order = asks.front();
      if (order->GetOrderType() == OrderType::FillAndKill) {
        CancelOrder(order->GetOrderID());
      }
    }

    return trades;
  }

public:
  Trades AddOrder(OrderPointer order) {
      std::scoped_lock ordersLock{ordersMutex_};
    if (orders_.contains(order->GetOrderID())) {
      return {};
    }
    if(order->GetOrderType()==OrderType::Market){
        if(order->GetSide()==Side::Buy && !asks_.empty()){
            const auto& [worstAsk,_]=*!asks_.empty();
            order->ToGoodTillCancel(worstAsk);

        }
        else if (order->GetSide()==Side::Sell && !bids_.empty()){
            const auto& [worstBid,_]=bids_.rbegin();
            order->ToGoodTillCancel(worstBid);
        }
        else{
            return {};
        }
    }

    if (order->GetOrderType() == OrderType::FillAndKill &&
        !CanMatch(order->GetSide(), order->GetPrice())) {
      return {};
    }
    if(order->GetOrderType()==OrderType::FillAOrKill && !CanMatch(order->GetSide(),order->GetPrice(),order->GetInitialQuantity())){
        return { };
    }

    OrderPointers::iterator iterator;
    if (order->GetSide() == Side::Buy) {
      auto &orders = bids_[order->GetPrice()];
      orders.push_back(order);
      iterator = std::next(orders.begin(), orders.size() - 1);
    } else {
      auto &orders = asks_[order->GetPrice()];
      orders.push_back(order);
      iterator = std::next(orders.begin(), orders.size() - 1);
    }

    orders_.insert({order->GetOrderID(), OrderEntry{order, iterator}});
    return MatchOrders();
  }

  void CancelOrder(OrderId orderId) {
    if (!orders_.contains(orderId)) {
      return;
    }

    const auto &[order, orderIterator] = orders_.at(orderId);
    orders_.erase(orderId);

    if (order->GetSide() == Side::Sell) {
      auto price = order->GetPrice();
      auto &orders = asks_.at(price);
      orders.erase(orderIterator);
      if (orders.empty()) {
        asks_.erase(price);
      }
    } else {
      auto price = order->GetPrice();
      auto &orders = bids_.at(price);
      orders.erase(orderIterator);
      if (orders.empty()) {
        bids_.erase(price);
      }
    }
  }

  std::size_t Size() const { return orders_.size(); }

  OrderBookLevelInfos GetOrderInfos() const {
    LevelInfos bidInfos, askInfos;
    bidInfos.reserve(orders_.size());
    askInfos.reserve(orders_.size());

    auto CreateLevelInfos = [](Price price,
                               const OrderPointers &orders) -> LevelInfo {
      return LevelInfo{
          price, static_cast<Quantity>(std::accumulate(
                     orders.begin(), orders.end(), static_cast<Quantity>(0),
                     [](Quantity runningSum, const OrderPointer &order) {
                       return runningSum + order->GetRemainingQuantity();
                     }))};
    };

    for (const auto &[price, orders] : bids_) {
      bidInfos.push_back(CreateLevelInfos(price, orders));
    }

    for (const auto &[price, orders] : asks_) {
      askInfos.push_back(CreateLevelInfos(price, orders));
    }

    return OrderBookLevelInfos{bidInfos, askInfos};
  }
};


 void OrderBook::OnOrderCancelled(OrderPointer order) {
     UpdateLevelData(order->GetPrice(),order->GetRemainingQuantity(),LevelData::Action::Remove);


 }
 void OrderBook::onOrderAdded(OrderPointer order) {
     UpdateLevelData(order->GetPrice(),order->GetInitialQuantity(),LevelData::Action::Add);

 }
 void OrderBook::OnOrderMatched(Price price,Quantity quantity,bool isFullyFilled){
     UpdateLevelData(price,quantity,isFullyFilled?LevelData::Action::Remove:LevelData::Action::MATCH);

 }
void OrderBook::UpdateLevelData(Price price, Quantity quantity, LevelData::Action action) {
     auto& data=data_[price];
     data.count_+=action==LevelData::Action::Remove ? -1 : action == LevelData::Action::ADD ? 1:0;
     if(Action==LevelData::Action::Remove || action== LevelData::Action::MATCH){
         data.quantity_-=quantity;
     }
     else{
         data.quantity_+=quantity;

     }
     if(data.count_==0){
         data_.erase(price);
     }
 }

