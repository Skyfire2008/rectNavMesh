#include "map.h"

#include <stdio.h>

#include <charconv>
#include <vector>

#include "../geom/point.h"
#include "../util/array2d.h"

using namespace util;

namespace path {

std::unique_ptr<Map> parseMap(size_t width, size_t height, std::string& hexString) {
    auto result = std::make_unique<Map>(width, height);

    size_t i = 0;                            // hexString index
    size_t j = 0;                            // data index
    for (; i < (width * height) / 4; i++) {  // don't read the character containing trailing bytes
        char c = hexString[i];
        int value = (c >= 'a') ? c - 'a' + 10 : c - '0';
        result->data[j++] = (value & 0b1000) != 0;
        result->data[j++] = (value & 0b0100) != 0;
        result->data[j++] = (value & 0b0010) != 0;
        result->data[j++] = (value & 0b0001) != 0;
    }

    // if there's an extra character containing leftover bits, covnert it, too
    int leftovers = (width * height) % 4;
    if (leftovers != 0) {
        char c = hexString[i];
        int value = (c >= 'a') ? c - 'a' + 10 : c - '0';
        int mask = 0b1000;
        for (int i = 0; i < leftovers; i++) {
            result->data[j++] = (value & mask) != 0;
            mask = mask >> 1;
        }
    }

    return result;
}

std::unique_ptr<Polygon<int>> mapToPolygon(Map& map) {
    auto labels = Array2d<int>(map.width, map.height);

    /**
     * @param start		contour starting point
     * @param map		map
     * @param labels	labels
     * @param isHole	if true, will trace hole contour with 8-neighbourhood and CCW, otherwise - polygon with 4-nrighbourhood and CW
     * @param label		label to set in labels
     */
    auto followContour = [](Point<int> start, Map& map, Array2d<int>& labels, bool isHole, int label) {
        /*auto isHole = [](Map& map, Point<int> pos){

        };*/

        std::vector<Point<int>> result;

        static Point<int> fourNeighbour[] = {
            Point<int>(0, -1),
            Point<int>(1, 0),
            Point<int>(0, 1),
            Point<int>(-1, 0),
        };

        static Point<int> eightNeighbour[] = {
            Point<int>(0, -1),
            Point<int>(1, -1),
            Point<int>(1, 0),
            Point<int>(1, 1),
            Point<int>(0, 1),
            Point<int>(-1, 1),
            Point<int>(-1, 0),
            Point<int>(-1, -1),
        };

        int startDirection = -1;
        int prevDirection = 0;
        Point<int> current = start;
        int mod = 0;
        int halfWay = 0;
        Point<int>* neighbours;

        if (isHole) {
            mod = 8;
            halfWay = 4;
            neighbours = eightNeighbour;
        } else {
            mod = 4;
            halfWay = 2;
            neighbours = fourNeighbour;
        }

        // initialize the algorithm by finding the next point from start
        for (int i = 0; i < mod; i++) {
            Point<int> foo = start + neighbours[i];
            if (foo.x >= 0 && foo.y >= 0 && foo.x < map.width && foo.y < map.height) {
                if (isHole == map.get(foo.x, foo.y)) {
                    start = foo;
                    startDirection = i;
                    prevDirection = i;
                    labels.set(foo.x, foo.y, label);
                    result.push_back(foo);
                    break;
                }
            }
        }

        while (true) {
            int direction = (prevDirection + halfWay) % mod;

            for (int i = 0; i < mod; i++) {
                int index = (i + direction) % mod;
            }
        }
    };

    for (size_t y = 0; y < map.height; y++) {
        int parentLabel = -1;

        for (size_t x = 0; x < map.width; x++) {
            auto currentLabel = labels.get(x, y);

            if (currentLabel == 0) {  // if current tile label is unassigned
                if (map.get(x, y)) {
                    if (parentLabel != -1) {
                    }
                } else {
                }
            } else {
                if (map.get(x, y)) {
                    // skip
                } else {
                    parentLabel = currentLabel;
                }
            }
        }
    }
}

void printMap(Map& map) {
    for (size_t y = 0; y < map.height; y++) {
        for (size_t x = 0; x < map.width; x++) {
            auto isWall = map.get(x, y);
            std::fprintf(stdout, "%c", isWall ? '#' : ' ');
        }
        fprintf(stdout, "\n");
    }
}

}  // namespace path