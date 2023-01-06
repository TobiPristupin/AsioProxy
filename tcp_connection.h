#ifndef PROXY_TCP_CONNECTION_H
#define PROXY_TCP_CONNECTION_H

#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/streambuf.hpp>

using tcp = boost::asio::ip::tcp;

class tcp_connection : public std::enable_shared_from_this<tcp_connection> {
public:
    tcp_connection(tcp::socket &&socket);

    void start();

private:
    tcp::socket socket;
    boost::asio::streambuf streambuf;
};


#endif //PROXY_TCP_CONNECTION_H
