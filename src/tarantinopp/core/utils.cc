#include "tarantinopp/core/utils.h"

#include <cctype>

namespace tarantinopp {
std::string byteVectorToString(ByteVector bv) {
  return std::string(bv.begin(), bv.end());
}

ByteVector stringToByteVector(std::string str) {
  return ByteVector(str.begin(), str.end());
}

std::string toLower(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return str;
}
}  // namespace tarantinopp