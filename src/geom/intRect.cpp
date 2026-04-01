#include "intRect.h"

namespace geom {
IntRect::IntRect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), area(width * height) {}
}  // namespace geom