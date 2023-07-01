#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include <functional>
#include <stdexcept>

#include "tarantinopp/concurrency/threadpool.h"
#include "tarantinopp/core/config.h"
#include "tarantinopp/core/log.h"
#include "tarantinopp/core/types.h"
#include "tarantinopp/network/base.h"

namespace tarantinopp {
namespace network {

class TCPSocketClient : public SocketClient {
 public:
  TCPSocketClient(int32_t sockFd, sockaddr_in addr,
                  std::shared_ptr<Logger> logger);
  virtual ~TCPSocketClient();

  // implementation of functions of Client base class
  ByteVector read(size_t numBytes) override;
  bool write(ByteVector bytes) override;

  std::string getClientInfo() override;
  std::shared_ptr<Logger> getLogger() override;

  void disconnect() override;

 private:
  int32_t m_socketFd;
  sockaddr_in m_addr;
  std::shared_ptr<Logger> m_logger;
};

class TCPSocket : public Socket {
 public:
  TCPSocket(SocketApplication app, const char* host, uint16_t port,
            uint32_t numBacklogs = 5, int32_t numThreads = -1,
            std::shared_ptr<Logger> logger = nullptr);
  virtual ~TCPSocket();

  // implementation of functions of Server base class

  void operator()() override;
  void shutdown() override;
  std::shared_ptr<Logger> getLogger() override;

 private:
  SocketApplication m_application;
  const char* m_host;
  uint16_t m_port;
  uint32_t m_numBacklogs;

  int m_listenerSocketFd;
  sockaddr_in m_ServerAddr;

  std::vector<std::shared_ptr<SocketClient>> m_clients;

  concurrency::Threadpool<SocketApplication, std::shared_ptr<SocketClient>>
      m_workerThreadpool;
  std::shared_ptr<Logger> m_logger;
};

}  // namespace network
}  // namespace tarantinopp