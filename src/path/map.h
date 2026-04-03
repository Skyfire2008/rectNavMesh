#pragma once

#include <memory>
#include <string>

#include "../util/array2d.h"

namespace path {
using Map = util::Array2d<bool>;

std::unique_ptr<Map> parseMap(size_t width, size_t height, std::string& hexString);

void printMap(Map& map);
}  // namespace path