#include "tarantinopp/server/server.h"

namespace tarantinopp {
namespace server {
ApplicationServer::ApplicationServer(std::string name, Handler handler,
                                     size_t blockSize,
                                     std::shared_ptr<Logger> logger)
    : m_name(name),
      m_handler(handler),
      m_blockSize(blockSize),
      m_logger(logger) {}

void ApplicationServer::operator()(
    std::shared_ptr<network::SocketClient> client) {
  auto [requestLine, headers, bufferedBody] = readRequest(client);

  Environment env = generateEnvironment(requestLine, headers);

  getLogger()->info(
      "[ENVIRONMENT] method: {0}, path: {1}, httpVersion: {2}, rawPath: {3}, "
      "queryString: {4}, rootPath: {5}",
      env.method, env.path, env.httpVersion, byteVectorToString(env.rawPath),
      byteVectorToString(env.queryString), env.rootPath);

  for (auto header : env.headers)
    getLogger()->info("[Header] {0}: {1}", byteVectorToString(header.first),
                      byteVectorToString(header.second));

  getLogger()->info("Buffered Body Size: {0}", bufferedBody.size());

  ByteVector responseBuffer;
  std::string response =
      "HTTP/1.1 200 OK\r\nCONNECTION: keep-alive\r\nCONTENT-TYPE: "
      "text/html\r\nCONTENT-LENGTH: "
      "48\r\n\r\n<h1>A message "
      "generated from example server</h1>";
  responseBuffer.insert(responseBuffer.end(), response.begin(), response.end());
  client->write(responseBuffer);

  client->disconnect();
}

std::shared_ptr<Logger> ApplicationServer::getLogger() {
  if (m_logger == nullptr)
    m_logger = std::make_shared<Logger>(m_name, LogLevel::debug);
  return m_logger;
}

std::tuple<ByteVector, ByteVector, ByteVector> ApplicationServer::readRequest(
    std::shared_ptr<network::SocketClient> client) {
  ByteVector buffer;

  // looping for request line
  auto isRequestLineEnd = [&buffer](int32_t requestLinePtr) -> bool {
    return (buffer[requestLinePtr] == '\r' &&
            buffer[requestLinePtr + 1] == '\n');
  };

  int32_t requestLinePtr = 0;
  while (true) {
    while (requestLinePtr < ((int32_t)buffer.size() - 1) &&
           !isRequestLineEnd(requestLinePtr))
      requestLinePtr++;
    if (requestLinePtr < ((int32_t)buffer.size() - 1) &&
        isRequestLineEnd(requestLinePtr))
      break;

    ByteVector data = client->read(m_blockSize);
    buffer.insert(buffer.end(), data.begin(), data.end());
  }
  // looping for headers
  auto isHeadersEnd = [&buffer](int32_t headerPtr) -> bool {
    return ((buffer[headerPtr] == '\r') && (buffer[headerPtr + 1] == '\n') &&
            (buffer[headerPtr + 2] == '\r') && (buffer[headerPtr + 3] == '\n'));
  };

  int32_t headersPtr = requestLinePtr + 2;
  while (true) {
    while (headersPtr < ((int32_t)buffer.size() - 3) &&
           !isHeadersEnd(headersPtr))
      headersPtr++;
    if (headersPtr < ((int32_t)buffer.size() - 3) && isHeadersEnd(headersPtr))
      break;

    ByteVector data = client->read(m_blockSize);
    buffer.insert(buffer.end(), data.begin(), data.end());
  }

  ByteVector requestLine(buffer.begin(), buffer.begin() + requestLinePtr);
  ByteVector headers(buffer.begin() + requestLinePtr + 2,
                     buffer.begin() + headersPtr + 2);
  ByteVector bufferedBody(buffer.begin() + headersPtr + 4, buffer.end());

  return {requestLine, headers, bufferedBody};
}

std::tuple<ByteVector, ByteVector, ByteVector>
ApplicationServer::parseRequestLine(ByteVector requestLine) {
  int32_t st = 0, en = 0;
  ByteVector method, path, httpVersion;

  while (en < (int32_t)requestLine.size()) {
    if (requestLine[en] == ' ') {
      method.insert(method.end(), requestLine.begin() + st,
                    requestLine.begin() + en);

      break;
    }
    ++en;
  }

  st = ++en;
  while (en < (int32_t)requestLine.size()) {
    if (requestLine[en] == ' ') {
      path.insert(path.end(), requestLine.begin() + st,
                  requestLine.begin() + en);

      break;
    }
    ++en;
  }

  st = ++en;
  httpVersion.insert(httpVersion.end(), requestLine.begin() + st + 5,
                     requestLine.end());

  return {method, path, httpVersion};
}

std::vector<std::pair<ByteVector, ByteVector>> ApplicationServer::parseHeaders(
    ByteVector headers) {
  std::vector<std::pair<ByteVector, ByteVector>> headersList;
  auto parseSingleHeader =
      [&headers](int32_t st, int32_t en) -> std::pair<ByteVector, ByteVector> {
    int32_t idx = st;
    while (idx < en - 1 && !(headers[idx] == ':' && headers[idx + 1] == ' '))
      ++idx;
    ByteVector k(headers.begin() + st, headers.begin() + idx),
        v(headers.begin() + idx + 2, headers.begin() + en);

    return {k, v};
  };

  int32_t st = 0, en = 0;
  while (en < (int32_t)headers.size() - 1) {
    if (headers[en] == '\r' && headers[en + 1] == '\n') {
      headersList.push_back(parseSingleHeader(st, en));
      st = en = en + 2;

    } else {
      ++en;
    }
  }

  return headersList;
}

Environment ApplicationServer::generateEnvironment(ByteVector requestLine,
                                                   ByteVector headers) {
  auto [method, path, httpVersion] = parseRequestLine(requestLine);
  auto headersList = parseHeaders(headers);

  return Environment(method, path, httpVersion, headersList);
}
}  // namespace server
}  // namespace tarantinopp