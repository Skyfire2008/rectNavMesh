#include "greedyDecomp.h"

#include "../util/array2d.h"

using namespace util;

namespace path {

IntRect GreedyDecomp::makeRect(int startX, int startY, Array2d<IntRect>& rects, Map& map) {
    auto maxArea = 0;
    auto maxAreaWidth = 0;
    auto maxAreaHeight = 0;
    auto maxWidth = map.width - startX;

    auto j = 0;
    auto curHeight = 1;
    auto completed = false;
    // process line-by-line while not completed
    while (!completed && j + startY < map.height) {
        auto currentArea = 0;

        // for every line, process max possible width
        for (int i = 0; i < maxWidth; i++) {
            auto x = i + startX;
            auto y = j + startY;

            // if current tile is not wall and not occupied by a rectangle
            if (!map.get(x, y) && !rects.get(x, y).isValid()) {
                // increment current area by current height
                currentArea += curHeight;
                // if current area greater than maximum area, update maximum area and its location
                if (currentArea > maxArea) {
                    maxArea = currentArea;
                    maxAreaWidth = i + 1;
                    maxAreaHeight = curHeight;
                }
                // if current tile is wall or occupied
            } else {
                // decrease max width
                maxWidth = i;
                if (maxWidth == 0) {
                    completed = true;
                }
                break;
            }
        }
        j++;
        curHeight++;
    }

    auto result = IntRect(startX, startY, maxAreaWidth, maxAreaHeight);
    // occupy the cells in rects array
    for (int i = 0; i < maxAreaWidth; i++) {
        for (auto j = 0; j < maxAreaHeight; j++) {
            auto x = i + startX;
            auto y = j + startY;
            rects.set(x, y, result);
        }
    }
    return result;
}

std::unique_ptr<std::vector<IntRect>> GreedyDecomp::getRectangles(Map& map) {
    auto result = std::make_unique<std::vector<IntRect>>();

    // 2d array, showing where rects are located
    auto rects = Array2d<IntRect>(map.width, map.height);

    size_t y = 0;
    // generate the rectangles
    while (y < map.height) {
        size_t x = 0;
        while (x < map.width) {
            // if current tile is empty
            if (!map.get(x, y)) {
                auto tileRect = rects.get(x, y);
                if (!tileRect.isValid()) {  // should only be invalid if it's default initialized
                    auto rect = GreedyDecomp::makeRect(x, y, rects, map);
                    result->push_back(rect);
                    x += rect.width;
                } else {
                    x += rects.get(x, y).width;
                }
            } else {
                x++;
            }
        }
        y++;
    }

    return result;
}
}  // namespace path