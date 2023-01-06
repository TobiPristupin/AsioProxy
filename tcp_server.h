#ifndef PROXY_TCP_SERVER_H
#define PROXY_TCP_SERVER_H

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind/bind.hpp>


using tcp = boost::asio::ip::tcp;

class tcp_server {

public:
    tcp_server(boost::asio::io_context& io_context, unsigned short port);
    void async_accept_incoming();
    unsigned short get_port() const;

private:
    boost::asio::io_context& io_context;
    tcp::acceptor acceptor;
    tcp::socket socket;
    unsigned short port;
};


#endif //PROXY_TCP_SERVER_H
