#include "tarantinopp/server/receive.h"

namespace tarantinopp {
namespace server {

ReceiveEvent::ReceiveEvent(ByteVector __body, bool __moreBody)
    : body(m_body),
      moreBody(m_moreBody),
      m_body(__body),
      m_moreBody(__moreBody) {}

ReceiveEvent::ReceiveEvent(const ReceiveEvent& other)
    : body(m_body),
      moreBody(m_moreBody),
      m_body(other.m_body),
      m_moreBody(other.m_moreBody) {}

ReceiveEvent::ReceiveEvent() : body(m_body), moreBody(m_moreBody) {}

ReceiveEvent& ReceiveEvent::operator=(const ReceiveEvent& other) {
  if (this == &other) {
    return *this;
  }
  m_body = other.body;
  m_moreBody = other.moreBody;
  return *this;
}

Receive::Receive(std::shared_ptr<network::SocketClient> client,
                 ByteVector bufferedBody, Environment env, size_t blockSize)
    : m_client(client),
      m_buffer(bufferedBody),
      m_blockSize(blockSize),
      m_contentReceived(0) {
  parseHeaders(env);
}

void Receive::parseHeaders(Environment env) {
  m_contentLength = 0;

  for (auto header : env.headers) {
    if (toLower(byteVectorToString(header.first)) ==
        http::HttpHeader::ContentLength) {
      m_contentLength =
          std::stoll(std::string(header.second.begin(), header.second.end()));
      m_receiveType = ReceiveType::ContentLength;
    }
  }
}

ReceiveEvent Receive::operator()() {
  if (m_receiveType == ReceiveType::ContentLength)
    return receiveByContentLength();

  return receiveByContentLength();  // default action
}

ReceiveEvent Receive::receiveByContentLength() {
  if (m_contentReceived >= m_contentLength)
    return ReceiveEvent(ByteVector(), false);

  int64_t remainingContentLength = m_contentLength - m_contentReceived;
  if (m_buffer.size() == 0) {
    ByteVector data = m_client->read(m_blockSize);
    m_buffer.insert(m_buffer.end(), data.begin(), data.end());
  }

  m_buffer.resize(std::min({(int64_t)m_buffer.size(), remainingContentLength}));
  m_contentReceived += m_buffer.size();
  ReceiveEvent re(m_buffer, (m_contentReceived < m_contentLength));
  m_buffer.clear();

  return re;
}

}  // namespace server
}  // namespace tarantinopp
