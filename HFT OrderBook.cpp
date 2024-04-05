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
         , asks_{asks}
    {}
    const LevelInfos& GetBids() const {return bids_;}
    const LevelInfos& GetBids() const {return asks_;}
    private:
    LevelInfos bids_;
    LevelInfos asks_;
    


}


int main(){


    return 0;

}