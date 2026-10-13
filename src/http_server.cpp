#include "../include/http_server.hpp"
#include <print>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

namespace http {
auto Server::StartServer() -> int {
  socket_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_ < 0) {
    std::println("Failed to create socket");
    exit(1);
  }

  auto bind_res = bind(socket_, reinterpret_cast<sockaddr *>(&socket_address_),
                       socket_address_len_);

  if (bind_res < 0) {
    std::println("Failed to bind socket");
    exit(1);
  }

  return 0;
}

auto Server::CloseServer() -> void {
  auto close_socket_result = close(socket_);
  if (close_socket_result < 0) {
    std::println("failed to close socket");
    exit(1);
  }

  close_socket_result = close(new_socket_);
  if (close_socket_result < 0) {
    std::println("failed to close new socket");
    exit(1);
  }
}

auto Server::StartListen() -> void {
  auto listen_result = listen(socket_, 6);
  if (listen_result < 0) {
    std::println("failed to listen");
    exit(1);
  }

  char ip_buffer[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &socket_address_.sin_addr, ip_buffer, sizeof(ip_buffer));

  std::println("\nListening on ADDRESS: {} PORT: {}\n", ip_buffer,
               ntohs(socket_address_.sin_port));
}

} // namespace http
