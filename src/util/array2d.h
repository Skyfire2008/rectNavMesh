#pragma once

#include <memory>

namespace util {
template <typename T>
class Array2d {
   public:
    const std::unique_ptr<T[]> data;
    const size_t width;
    const size_t height;

    Array2d(size_t width, size_t height) : width(width), height(height), data(std::make_unique<T[]>(width * height)) {}

    inline T& get(size_t x, size_t y) {
        return data[y * width + x];
    }

    inline void set(size_t x, size_t y, T& value) {
        data[y * width + x] = value;
    }
};

}  // namespace util