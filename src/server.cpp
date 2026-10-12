#include "../include/http_server.hpp"

auto main() -> int {
  http::Server server{"0.0.0.0", 8123};
  return 0;
}
