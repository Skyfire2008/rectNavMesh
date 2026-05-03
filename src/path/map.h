#pragma once

#include <memory>
#include <string>

#include "../geom/polygon.h"
#include "../util/array2d.h"

using namespace geom;

namespace path {
using Map = util::Array2d<bool>;

std::unique_ptr<Map> parseMap(size_t width, size_t height, std::string& hexString);

/**
 * Convert walkable areas of the map into an array of polygons using Suzuki-Abe contour tracing algorithm
 * @param	map		map to process
 * @return 			Pointer to vector of polygons comprising the walkable area
 */
std::unique_ptr<Polygon<int>> mapToPolygon(Map& map);

void printMap(Map& map);
}  // namespace path