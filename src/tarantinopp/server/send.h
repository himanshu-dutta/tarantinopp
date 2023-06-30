#pragma once

#include <functional>
#include <memory>

#include "tarantinopp/core/types.h"
#include "tarantinopp/network/base.h"
#include "tarantinopp/server/environ.h"

namespace tarantinopp {
namespace server {
class SendEvent {
 public:
  SendEvent(std::string __type, std::string __status,
            std::vector<std::pair<ByteVector, ByteVector>> __headers);

  SendEvent(std::string __type, ByteVector __body, bool __moreBody);
  SendEvent();
  SendEvent& operator=(const SendEvent& other);

 public:
  static const std::string EventTypeStart;
  static const std::string EventTypeBody;

 public:
  const std::string& eventType;
  const std::string& status;
  const std::vector<std::pair<ByteVector, ByteVector>>& headers;
  const ByteVector& body;
  const bool& moreBody;

 private:
  std::string m_eventType;
  std::string m_status;
  std::vector<std::pair<ByteVector, ByteVector>> m_headers;
  ByteVector m_body;
  bool m_moreBody;
};

using SendFn = std::function<void(SendEvent)>;

class Send {
 public:
  Send(std::shared_ptr<network::SocketClient> client, Environment env);
  void operator()(SendEvent se);

 private:
  void sendStart(SendEvent& se);
  void sendBody(SendEvent& se);

 private:
  std::shared_ptr<network::SocketClient> m_client;
  std::string m_httpVersion;
  bool m_socketClosed;
};
}  // namespace server
}  // namespace tarantinopp