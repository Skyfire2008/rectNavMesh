#pragma once

#include <memory>
#include <vector>

#include "../util/array2d.h"
#include "rectDecomp.h"

using namespace geom;
using namespace util;

namespace path {

/**
 *
 */
class GreedyDecomp : public RectDecomp {
   public:
    std::unique_ptr<std::vector<IntRect>> getRectangles(Map& map);

   private:
    /**
     * Helper function, creates a largest possible rectangle at given coordinates
     * @param startX left coordinate
     * @param startY top coordiante
     * @param rects  2d array of tiles occupied by rectangles
     * @param map	 map(2d array of walls)
     * @return IntRect
     */
    static IntRect makeRect(int startX, int startY, Array2d<IntRect>& rects, Map& map);
};

}  // namespace path