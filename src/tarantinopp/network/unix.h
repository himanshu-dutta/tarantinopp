#pragma once

#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include <filesystem>
#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

#include "tarantinopp/concurrency/threadpool.h"
#include "tarantinopp/core/config.h"
#include "tarantinopp/core/log.h"
#include "tarantinopp/core/types.h"
#include "tarantinopp/network/base.h"

namespace tarantinopp {
namespace network {
class UnixSocketClient : public SocketClient {
 public:
  UnixSocketClient(int32_t socketFd, sockaddr_un addr,
                   std::shared_ptr<Logger> logger);
  virtual ~UnixSocketClient();

  // implementation of functions of Client base class
  ByteVector read(size_t numBytes) override;
  bool write(ByteVector bytes) override;

  std::string getClientInfo() override;
  std::shared_ptr<Logger> getLogger() override;

  void disconnect() override;

 private:
  uint32_t m_socketFd;
  sockaddr_un m_addr;
  std::shared_ptr<Logger> m_logger;
};

class UnixSocket : public Socket {
 public:
  UnixSocket(std::string socketFilePath = "", uint32_t numBacklogs = 5,
             int32_t numThreads = -1, std::shared_ptr<Logger> logger = nullptr);
  virtual ~UnixSocket();

  // implementation of functions of Server base class
  void operator()(SocketApplication app) override;
  void shutdown() override;

  std::shared_ptr<Logger> getLogger() override;

 private:
  void populateServerAddress();

 private:
  int32_t m_listenerSocketFd;
  uint32_t m_numBacklogs;
  std::string m_socketFilePath;
  sockaddr_un m_serverAddr;

  std::vector<std::shared_ptr<SocketClient>> m_clients;
  concurrency::Threadpool<SocketApplication, std::shared_ptr<SocketClient>>
      m_workerThreadpool;
  std::shared_ptr<Logger> m_logger;
};
}  // namespace network
}  // namespace tarantinopp