#include "../include/http_server.hpp"
#include <csignal>

volatile sig_atomic_t running = 1;

void HandleSigint(int) { running = 0; }

auto main() -> int {
  struct sigaction sa{};
  sa.sa_handler = HandleSigint;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sigaction(SIGINT, &sa, nullptr);

  http::Server server{"127.0.0.1", 8123};
  server.StartServer();
  server.StartListen();

  while (running) {
    server.AcceptConnection();
    server.ReadFromSocket();

    std::string body = "<h1>Hello from my server</h1>";
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    response += "Connection: close \r\n";
    response += "\r\n";
    response += body;

    server.Write(response, response.size());
  }

  server.CloseServer();
  return 0;
}
