#include "net_utils.h"


std::vector<boost::asio::ip::address> net_utils::ip_from_url(const std::string& url, boost::asio::io_context &io_context) {
    std::vector<boost::asio::ip::address> ips;

    tcp::resolver resolver(io_context);
    tcp::resolver::query query(url, "");
    for (auto it = resolver.resolve(query); it != tcp::resolver::iterator(); it++){
        ips.push_back(tcp::endpoint(*it).address());
    }

    return ips;
}
