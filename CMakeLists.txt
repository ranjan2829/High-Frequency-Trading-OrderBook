cmake_minimum_required(VERSION 3.27)
project(Orderbook_market)

set(CMAKE_CXX_STANDARD 14)

add_executable(Orderbook_market
        "HFT OrderBook.cpp"
        Order.h)
