cmake_minimum_required(VERSION 3.9)
project(eth-rpc-demo-cpp)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(eth-rpc-demo-cpp main.cpp ethrpc.h )
target_link_libraries(eth-rpc-demo-cpp jsoncpp jsonrpccpp-common jsonrpccpp-client)

