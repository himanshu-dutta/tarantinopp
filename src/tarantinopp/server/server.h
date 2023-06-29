#pragma once
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "tarantinopp/core/config.h"
#include "tarantinopp/core/log.h"
#include "tarantinopp/core/types.h"
#include "tarantinopp/core/utils.h"
#include "tarantinopp/network/base.h"
#include "tarantinopp/server/environ.h"

namespace tarantinopp {
namespace server {
using Send = int;
using Receive = int;

using Handler = std::function<void(Environment, Send, Receive)>;

class ApplicationServer {
 public:
  ApplicationServer(std::string name, Handler handler,
                    size_t blockSize = MAX_BUFFER_SIZE,
                    std::shared_ptr<Logger> logger = nullptr);
  void operator()(std::shared_ptr<network::SocketClient>);
  std::shared_ptr<Logger> getLogger();

 private:
  std::tuple<ByteVector, ByteVector, ByteVector> readRequest(
      std::shared_ptr<network::SocketClient> client);
  Environment generateEnvironment(ByteVector requestLine, ByteVector headers);
  void generateReceive(std::shared_ptr<network::SocketClient> client,
                       ByteVector bufferedBody);
  void generateSend(std::shared_ptr<network::SocketClient> client);

  std::tuple<ByteVector, ByteVector, ByteVector> parseRequestLine(
      ByteVector requestLine);
  std::vector<std::pair<ByteVector, ByteVector>> parseHeaders(
      ByteVector headers);

 private:
  std::string m_name;
  Handler m_handler;
  size_t m_blockSize;
  std::shared_ptr<Logger> m_logger;
};
}  // namespace server
}  // namespace tarantinopp
