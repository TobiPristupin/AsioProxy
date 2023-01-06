#ifndef PROXY_NET_UTILS_H
#define PROXY_NET_UTILS_H


#include <string>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

using tcp = boost::asio::ip::tcp;

class net_utils {
public:
    static std::vector<boost::asio::ip::address> ip_from_url(const std::string& url, boost::asio::io_context &io_context);
};


#endif //PROXY_NET_UTILS_H
