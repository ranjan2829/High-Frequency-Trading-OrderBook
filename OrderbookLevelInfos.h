//
// Created by Ranjan shahaji shitole on 02/06/24.
//

#pragma once
#include "LevelInfo.h"
 class OrderbookLevelInfos{
public :
    OrderbookLevelInfos(const LevelInfos& bids,LevelInfos& asks)
                :bids_{bids}
                ,asks_{asks}
    {}
    const LevelInfos& GetBids() const {return bids_;}
    const LevelInfps& GetAsks() const {return asks_;}

private:
    LevelInfos bids_;
    LevelInfos asks_;

};