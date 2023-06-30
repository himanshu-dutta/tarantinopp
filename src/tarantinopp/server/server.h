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
#include "tarantinopp/server/receive.h"
#include "tarantinopp/server/send.h"

namespace tarantinopp {
namespace server {

using Application = std::function<void(Environment, ReceiveFn, SendFn)>;

class ApplicationServer {
 public:
  ApplicationServer(std::string name, Application application,
                    size_t blockSize = MAX_BUFFER_SIZE,
                    std::shared_ptr<Logger> logger = nullptr);
  void operator()(std::shared_ptr<network::SocketClient>);
  std::shared_ptr<Logger> getLogger();

 private:
  std::tuple<ByteVector, ByteVector, ByteVector> readRequest(
      std::shared_ptr<network::SocketClient> client);
  Environment generateEnvironment(ByteVector requestLine, ByteVector headers);
  ReceiveFn generateReceive(std::shared_ptr<network::SocketClient> client,
                            ByteVector bufferedBody, Environment env);
  SendFn generateSend(std::shared_ptr<network::SocketClient> client,
                      Environment env);

  std::tuple<ByteVector, ByteVector, ByteVector> parseRequestLine(
      ByteVector requestLine);
  std::vector<std::pair<ByteVector, ByteVector>> parseHeaders(
      ByteVector headers);

 private:
  std::string m_name;
  Application m_application;
  size_t m_blockSize;
  std::shared_ptr<Logger> m_logger;
};
}  // namespace server
}  // namespace tarantinopp
