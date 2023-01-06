#include <iostream>
#include "tcp_server.h"
#include "tcp_connection.h"

tcp_server::tcp_server(boost::asio::io_context &io_context, unsigned short port)
    :   io_context(io_context),
        acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
        socket(io_context),
        port(port)
        {}

unsigned short tcp_server::get_port() const {
    return port;
}

void tcp_server::async_accept_incoming() {
    acceptor.async_accept(socket, [&] (boost::system::error_code ec) {
        if (ec){
            std::cerr << ec.message() << "\n";
            return;
        }

        std::make_shared<tcp_connection>(std::move(socket))->start();
        async_accept_incoming();
    });
}



