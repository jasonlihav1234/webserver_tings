#pragma once

#include <algorithm>
#include <arpa/inet.h>
#include <string>

namespace http {
class Server {
public:
  Server(std::string ip_address, int port)
      : ip_address_{ip_address}, port_{port}, socket_{}, new_socket_{},
        incoming_message_{}, socket_address_{},
        socket_address_len_{sizeof(socket_address_)}, server_message_{} {

    socket_address_.sin_family = AF_INET;
    socket_address_.sin_port = htons(port_);
    std::fill_n(socket_address_.sin_zero, 8,
                0); // fill first 8 elements of arr to 0
    socket_address_.sin_addr.s_addr = inet_addr(ip_address_.c_str());
  }
  ~Server() { CloseServer(); }

private:
  std::string ip_address_;
  int port_;
  int socket_;
  int new_socket_;
  long long incoming_message_;
  struct sockaddr_in socket_address_;
  uint32_t socket_address_len_;
  std::string server_message_;

  auto StartServer() -> int;
  auto CloseServer() -> void;
};
}; // namespace http
