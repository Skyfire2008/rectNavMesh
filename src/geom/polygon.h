#pragma once

#include <vector>

namespace geom {
template <typename T>
class Polygon {
   public:
    std::vector<Point<T>> points;
    std::Vector<std::vector<Point<T>>> holes;

    Polygon() {};
};
}  // namespace geom