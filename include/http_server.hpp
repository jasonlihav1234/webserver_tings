#pragma once

#include <arpa/inet.h>
#include <string>

namespace http {
class Server {
public:
  Server();
  ~Server();

private:
  std::string ip_address_;
  int port_;
  int socket_;
  int new_socket_;
  long long incoming_message_;
  struct sockaddr_in socket_address_;
  uint32_t socket_address_len_;
  std::string servere_message_;

  auto StartServer() -> int;
  auto CloseServer(int server_socket) -> void;
};
}; // namespace http
