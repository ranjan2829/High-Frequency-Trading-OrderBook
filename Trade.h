//
// Created by Ranjan shahaji shitole on 02/06/24.

#pragma once
#include "TradeInfo.h"
using namespace std;

class Trade{
public:
    Trade(const TradeInfo& bidTrade , const TradeInfo& askTrade)
         :bidTrade_{bidTrade}
         ,askTrade_{askTrade}
    {}
    const TradeInfo& GetBIdTrade() const {return bidTrade_;}
    const TradeInfo& GetAskTrade() const {return askTrade_;}


private:
    TradeInfo bidTrade_;
    TradeInfo askTrade_;




};
using Trades=std::vector<Trade>;

