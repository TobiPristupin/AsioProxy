cmake_minimum_required(VERSION 3.21)
project(proxy)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(proxy main.cpp tcp_server.cpp tcp_server.h tcp_connection.cpp tcp_connection.h net_utils.h net_utils.cpp)
add_executable(proxy2 main_sockets.cpp)
target_link_libraries(proxy ${Boost_LIBRARIES})
