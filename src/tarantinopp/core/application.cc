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
  getLogger()->info("[🚀] method: {0}", env.method);
  getLogger()->info("[🚀] path: {0}", env.path);
  getLogger()->info("[🚀] httpVersion: {0}", env.httpVersion);
  getLogger()->info("[🚀] rawPath: {0}", byteVectorToString(env.rawPath));
  getLogger()->info("[🚀] queryString: {0}",
                    byteVectorToString(env.queryString));
  getLogger()->info("[🚀] rootPath: {0}", env.rootPath);

  for (auto header : env.headers)
    getLogger()->info("[✨] {0}: {1}", byteVectorToString(header.first),
                      byteVectorToString(header.second));

  bool moreBody = false;
  int64_t bodySize = 0;
  int32_t numTurns = 0;
  do {
    server::ReceiveEvent re = receive();
    moreBody = re.moreBody;
    bodySize += re.body.size();
    numTurns++;
  } while (moreBody);
  getLogger()->info("[🔥] Received {0} Bytes of the body in {1} turns",
                    bodySize, numTurns);
  getLogger()->trace("###########################################");

  ////////////
  // RESPONSE
  ////////////
  send(server::SendEvent(server::SendEvent::EventTypeStart,
                         http::HttpStatus::STATUS_200_OK,
                         std::vector<std::pair<ByteVector, ByteVector>>{
                             {stringToByteVector("Content-Type"),
                              stringToByteVector("text/html")}}));
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