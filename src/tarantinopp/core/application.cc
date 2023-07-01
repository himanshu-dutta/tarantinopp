#include "tarantinopp/core/application.h"

#include "tarantinopp/core/utils.h"
#include "tarantinopp/protocol/http/headers.h"
#include "tarantinopp/protocol/http/status.h"
#include "tarantinopp/server/receive.h"
#include "tarantinopp/server/send.h"

namespace tarantinopp {

Application::Application(std::string name, std::shared_ptr<Logger> logger)
    : m_name(name), m_logger(logger) {}

void Application::operator()(server::Environment env, server::ReceiveFn receive,
                             server::SendFn send) {
  ////////////
  // REQUEST
  ////////////
  getLogger()->trace("###########################################");
  getLogger()->info(
      "[✅] method: {0}, path: {1}, httpVersion: {2}, rawPath: {3}, "
      "queryString: {4}, rootPath: {5}",
      env.method, env.path, env.httpVersion, byteVectorToString(env.rawPath),
      byteVectorToString(env.queryString), env.rootPath);
  for (auto header : env.headers)
    getLogger()->info("[✨] {0}: {1}", byteVectorToString(header.first),
                      byteVectorToString(header.second));
  bool moreBody = false;
  do {
    server::ReceiveEvent re = receive();
    moreBody = re.moreBody;
    getLogger()->info("[🎊] Received {} Bytes of the body", re.body.size());
  } while (moreBody);
  getLogger()->trace("###########################################");

  ////////////
  // RESPONSE
  ////////////
  std::vector<std::pair<ByteVector, ByteVector>> responseHeaders{
      {stringToByteVector("Content-Type"), stringToByteVector("text/html")}};

  send(server::SendEvent(server::SendEvent::EventTypeStart,
                         http::HttpStatus::STATUS_200_OK, responseHeaders));
  send(server::SendEvent(
      server::SendEvent::EventTypeBody,
      stringToByteVector("<h1>A message generated from example server</h1>"),
      false));
}

std::shared_ptr<Logger> Application::getLogger() {
  if (m_logger == nullptr) throw std::runtime_error("logger not initiated");
  return m_logger;
}

}  // namespace tarantinopp