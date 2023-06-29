#include <chrono>
#include <iostream>
#include <mutex>

#include "tarantinopp/concurrency/threadpool.h"
#include "tarantinopp/core/server.h"
#include "tarantinopp/core/types.h"
#include "tarantinopp/network/base.h"
#include "tarantinopp/network/tcp.h"
#include "tarantinopp/network/unix.h"

void threadpool_example();
void socket_tcp_example();
void socket_unix_example();
void application_server_example();

int main() {
  //   threadpool_example();
  //   socket_tcp_example();
  // socket_unix_example();
  application_server_example();
  return 0;
}

void threadpool_example() {
  tarantinopp::concurrency::Threadpool<std::function<void(int&)>, int&> tp(256);
  std::cout << "going to run the threadpool now...\n";
  std::mutex mu;
  int x = 0;
  const auto task = [&x](int&) { x++; };

  for (int idx = 0; idx < 100000; ++idx) tp.queueJob(task, idx);
  tp.close();

  std::cout << "x: " << x << std::endl;
}

void socket_tcp_example() {
  using namespace tarantinopp;
  using namespace tarantinopp::network;

  const size_t BUFF_SIZE = 1024;
  std::shared_ptr<Logger> logger(new Logger("example", LogLevel::trace));
  TCPSocket socket("0.0.0.0", 8000, 5, 1024, logger);
  socket.getLogger()->info("Starting the server...");
  socket([&socket](std::shared_ptr<SocketClient> client) {
    ByteVector req_buff;
    req_buff = client->read(BUFF_SIZE);
    std::string req_str(req_buff.begin(), req_buff.end());
    std::string req_hl = req_str.substr(0, req_str.find("\r\n"));

    ByteVector resp_buff;
    std::string response =
        "HTTP/1.1 200 OK\r\nCONNECTION: keep-alive\r\nCONTENT-TYPE: "
        "text/html\r\nCONTENT-LENGTH: "
        "48\r\n\r\n<h1>A message "
        "generated from example server</h1>";
    resp_buff.insert(resp_buff.end(), response.begin(), response.end());
    client->write(resp_buff);

    socket.getLogger()->info("{0} -- \"{1}\" {2}", client->getClientInfo(),
                             req_hl, 200);
    client->disconnect();
  });
}

void socket_unix_example() {
  using namespace tarantinopp;
  using namespace tarantinopp::network;

  const size_t BUFF_SIZE = 1024;

  std::shared_ptr<Logger> logger(new Logger("example", LogLevel::trace));
  UnixSocket socket("example.sock", 5, 1024, logger);
  socket.getLogger()->info("Starting the server...");

  socket([&socket](std::shared_ptr<SocketClient> client) {
    ByteVector req_buff;
    req_buff = client->read(BUFF_SIZE);
    std::string req_str(req_buff.begin(), req_buff.end());
    std::string req_hl = req_str.substr(0, req_str.find("\r\n"));

    ByteVector resp_buff;
    std::string response =
        "HTTP/1.1 200 OK\r\nCONNECTION: keep-alive\r\nCONTENT-TYPE: "
        "text/html\r\nCONTENT-LENGTH: "
        "48\r\n\r\n<h1>A message "
        "generated from example server</h1>";
    resp_buff.insert(resp_buff.end(), response.begin(), response.end());
    client->write(resp_buff);

    socket.getLogger()->info("{0} -- \"{1}\" {2}", client->getClientInfo(),
                             req_hl, 200);
    client->disconnect();
  });
}

void application_server_example() {
  using namespace tarantinopp;
  using namespace tarantinopp::network;

  std::shared_ptr<Logger> logger(new Logger("example", LogLevel::trace));
  ApplicationServer as("example", nullptr, 2048, logger);
  UnixSocket server("example.sock", 5, 1024, logger);
  //   TCPSocket server("0.0.0.0", 8000, 5, 1024, logger);
  server(as);
}