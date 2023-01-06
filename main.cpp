#include <iostream>
#include <boost/asio.hpp>
#include "tcp_server.h"
#include "net_utils.h"

#define PORT 52378

int main(int argc, char* argv[]) {
    boost::asio::io_context io_context;
    tcp_server server(io_context, PORT);
    server.async_accept_incoming();
    io_context.run();
}
