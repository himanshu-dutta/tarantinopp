#pragma once

#include <functional>

#include "tarantinopp/core/config.h"
#include "tarantinopp/core/types.h"
#include "tarantinopp/network/base.h"
#include "tarantinopp/protocol/http/headers.h"
#include "tarantinopp/server/environ.h"

namespace tarantinopp {
namespace server {
class ReceiveEvent {
 public:
  ReceiveEvent(ByteVector __body, bool __moreBody);
  ReceiveEvent(const ReceiveEvent& other);
  ReceiveEvent& operator=(const ReceiveEvent& other);

 public:
  const ByteVector& body;
  const bool& moreBody;

 private:
  ByteVector m_body;
  bool m_moreBody;
};

using ReceiveFn = std::function<ReceiveEvent()>;

enum class ReceiveType { ContentLength };

class Receive {
 public:
  Receive(std::shared_ptr<network::SocketClient> client,
          ByteVector bufferedBody, Environment env,
          size_t blockSize = MAX_BUFFER_SIZE);
  Receive(const Receive& other);
  ReceiveEvent operator()();

 private:
  void parseHeaders(Environment env);
  ReceiveEvent receiveByContentLength();

 private:
  std::shared_ptr<network::SocketClient> m_client;
  ByteVector m_buffer;
  ReceiveType m_receiveType;

  int64_t m_contentLength;
  size_t m_blockSize;
  int64_t m_contentReceived;
};
}  // namespace server
}  // namespace tarantinopp