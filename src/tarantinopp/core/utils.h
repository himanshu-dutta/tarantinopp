#pragma once

#include <algorithm>
#include <string>

#include "tarantinopp/core/types.h"

namespace tarantinopp {

std::string byteVectorToString(ByteVector bv);
ByteVector stringToByteVector(std::string str);
std::string toLower(std::string);

}  // namespace tarantinopp