#include "tarantinopp/core/utils.h"

namespace tarantinopp {
std::string byteVectorToString(ByteVector bv) {
  return std::string(bv.begin(), bv.end());
}
}  // namespace tarantinopp