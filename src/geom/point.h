#pragma once

#include <type_traits>

namespace geom {
template <typename T>
// TODO: replace with GLM, also use precompiled headers
class Point {
    static_assert(std::is_arithmetic_v<T>, "Point only accepts numeric types");

   public:
    T x;
    T y;

    Point(T x, T y) : x(x), y(y) {}

    Point operator+(Point& other) {
        return Point(this.x + other.x, this.y + other.y);
    }

    Point& operator+=(Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};
}  // namespace geom