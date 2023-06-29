#include "tarantinopp/server/environ.h"

namespace tarantinopp {
namespace server {
Environment::Environment(
    ByteVector __method, ByteVector __rawPath, ByteVector __httpVersion,
    std::vector<std::pair<ByteVector, ByteVector>> __headersList)
    : method(m_method),
      path(m_path),
      httpVersion(m_httpVersion),
      rawPath(m_rawPath),
      queryString(m_queryString),
      rootPath(m_rootPath),
      headers(m_headers) {
  m_method = byteVectorToString(__method);
  m_rawPath = __rawPath;
  m_httpVersion = byteVectorToString(__httpVersion);
  m_rootPath = getcwd(nullptr, 0);
  m_headers = __headersList;
  parseRawPath();
}

void Environment::parseRawPath() {
  int32_t idx = 0;
  while (idx < (int32_t)m_rawPath.size() && m_rawPath[idx] != '?') ++idx;
  m_path = std::string(m_rawPath.begin(), m_rawPath.begin() + idx);
  if (idx < (int32_t)m_rawPath.size())
    m_queryString.insert(m_queryString.end(), m_rawPath.begin() + idx + 1,
                         m_rawPath.end());
}
}  // namespace server
}  // namespace tarantinopp