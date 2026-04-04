#include "intRect.h"

namespace geom {
IntRect::IntRect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), area(width * height) {}

void to_json(json& j, const IntRect& rect) {
    j = json{{"x", rect.x}, {"y", rect.y}, {"width", rect.width}, {"height", rect.height}};
}
}  // namespace geom