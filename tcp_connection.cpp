#include <boost/asio/read_until.hpp>
#include <iostream>
#include "tcp_connection.h"
#include "net_utils.h"

tcp_connection::tcp_connection(tcp::socket &&socket) : socket(std::move(socket)) {}

void tcp_connection::start() {
    boost::asio::async_read_until(socket, streambuf, "\n",
                                  [self = shared_from_this()](boost::system::error_code ec,
                                                              std::size_t bytes_transferred) {
                                      if (ec) {
                                          std::cerr << ec.message() << "\n";
                                          return;
                                      }

                                      std::string server_url = "tcpbin.com";
                                      unsigned short port = 4242;
                                      boost::asio::io_context io_context;
                                      tcp::endpoint endpoint(net_utils::ip_from_url(server_url, io_context)[0], port);
                                      tcp::socket server_socket(io_context);
                                      server_socket.connect(endpoint);


                                      server_socket.write_some(boost::asio::buffer(self->streambuf.data(), 1024));
                                      self->streambuf.consume(self->streambuf.capacity());
                                      server_socket.wait(server_socket.wait_read);
                                      std::vector<char> v(1024);
                                      server_socket.read_some(boost::asio::buffer(v, v.size()));
                                      self->socket.write_some(boost::asio::buffer(v, v.size()));


//        server_socket.async_write_some(self->streambuf, [&self, &server_socket] (boost::system::error_code ec, std::size_t bytes_transferred) {
//            boost::asio::streambuf sb;
//            server_socket.async_read_some(sb, [&self, &sb] (boost::system::error_code ec, std::size_t bytes_transferred) {
//                self->socket.async_write_some(sb, [&self] (boost::system::error_code ec, std::size_t bytes_transferred) {
//                    std::cout << "writing done\n";
//                });
//            });
//        });

                                      self->start();
                                  });
}
