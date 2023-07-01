#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "tarantinopp/core/log.h"
#include "tarantinopp/core/types.h"

namespace tarantinopp {
namespace network {
class SocketClient {
 public:
  virtual ByteVector read(size_t) = 0;
  virtual bool write(ByteVector) = 0;
  virtual void disconnect() = 0;
  virtual std::string getClientInfo() = 0;
  virtual std::shared_ptr<Logger> getLogger() = 0;
};

using SocketApplication = std::function<void(std::shared_ptr<SocketClient>)>;

class Socket {
 public:
  virtual void operator()() = 0;
  virtual void shutdown() = 0;
  virtual std::shared_ptr<Logger> getLogger() = 0;
};
}  // namespace network
}  // namespace tarantinopp