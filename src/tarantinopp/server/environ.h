#pragma once

#include <unistd.h>

#include <string>
#include <utility>
#include <vector>

#include "tarantinopp/core/types.h"
#include "tarantinopp/core/utils.h"

namespace tarantinopp {
namespace server {
class Environment {
 public:
  Environment(ByteVector method, ByteVector rawPath, ByteVector httpVersion,
              std::vector<std::pair<ByteVector, ByteVector>> headersList);

 private:
  void parseRawPath();

 public:
  const std::string& method;
  const std::string& path;
  const std::string& httpVersion;
  const ByteVector& rawPath;
  const ByteVector& queryString;
  const std::string& rootPath;
  const std::vector<std::pair<ByteVector, ByteVector>>& headers;

 private:
  std::string m_method;
  std::string m_path;
  std::string m_httpVersion;
  ByteVector m_rawPath;
  ByteVector m_queryString;
  std::string m_rootPath;
  std::vector<std::pair<ByteVector, ByteVector>> m_headers;
};
}  // namespace server
}  // namespace tarantinopp