#include "tarantinopp/server/send.h"

namespace tarantinopp {
namespace server {
const std::string SendEvent::EventTypeStart = "start";
const std::string SendEvent::EventTypeBody = "body";

SendEvent::SendEvent(std::string __type, std::string __status,
                     std::vector<std::pair<ByteVector, ByteVector>> __headers)
    : eventType(m_eventType),
      status(m_status),
      headers(m_headers),
      body(m_body),
      moreBody(m_moreBody),
      m_eventType(__type),
      m_status(__status),
      m_headers(__headers) {}

SendEvent::SendEvent(std::string __type, ByteVector __body, bool __moreBody)
    : eventType(m_eventType),
      status(m_status),
      headers(m_headers),
      body(m_body),
      moreBody(m_moreBody),
      m_eventType(__type),
      m_body(__body),
      m_moreBody(__moreBody) {}

SendEvent::SendEvent()
    : eventType(m_eventType),
      status(m_status),
      headers(m_headers),
      body(m_body),
      moreBody(m_moreBody) {}

SendEvent& SendEvent::operator=(const SendEvent& other) {
  if (this == &other) {
    return *this;
  }
  m_eventType = other.eventType;
  m_status = other.status;
  m_headers = other.headers;
  m_body = other.body;
  m_moreBody = other.moreBody;

  return *this;
}

Send::Send(std::shared_ptr<network::SocketClient> client, Environment env)
    : m_client(client),
      m_httpVersion("HTTP/" + env.httpVersion),
      m_socketClosed(false) {}

void Send::operator()(SendEvent se) {
  if (se.eventType == SendEvent::EventTypeStart)
    sendStart(se);
  else if (se.eventType == SendEvent::EventTypeBody)
    sendBody(se);
}

void Send::sendStart(SendEvent& se) {
  std::string responseStart;
  responseStart += m_httpVersion + " ";
  responseStart += se.status;
  responseStart += "\r\n";
  for (auto header : se.headers)
    responseStart += byteVectorToString(header.first) + ": " +
                     byteVectorToString(header.second) + "\r\n";
  responseStart += "\r\n";

  m_client->write(stringToByteVector(responseStart));
}

void Send::sendBody(SendEvent& se) {
  if (m_socketClosed) throw std::runtime_error("socket already closed");

  m_client->write(se.body);
  if (!se.moreBody) {
    m_client->disconnect();
    m_socketClosed = true;
  }
}

}  // namespace server
}  // namespace tarantinopp