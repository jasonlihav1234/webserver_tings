#include "../include/http_server.hpp"
#include <print>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

namespace http {
Server::Server() {}
Server::~Server() {}

auto Server::StartServer() -> int {
  auto server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket < 0) {
    std::println("Failed to create socket");
    exit(1);
  }

  return server_socket;
}

auto Server::CloseServer(int server_socket) -> void {
  auto close_socket_result = close(server_socket);
  if (close_socket_result < 0) {
    std::println("failed to close socket");
    exit(1);
  }
}

} // namespace http
