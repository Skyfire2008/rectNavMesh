#pragma once

namespace geom {

class IntRect {
   public:
    int x;
    int y;
    int width;
    int height;
    int area;

    IntRect(int x = 0, int y = 0, int width = 0, int height = 0);
    inline bool isValid() {
        return area > 0;
    }
};
}  // namespace geom