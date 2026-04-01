#pragma once

#include <memory>
#include <vector>

#include "../geom/intRect.h"
#include "map.h"

using namespace geom;

namespace path {

/**
 * Performs a rectangle decomposition of the walkable area of the map
 */
class RectDecomp {
   public:
    virtual std::unique_ptr<std::vector<IntRect>> getRectangles(Map& map) = 0;
    virtual ~RectDecomp() = default;
};

}  // namespace path