#pragma once

class Map {
   public:
    bool* const walls;
    const size_t width;
    const size_t height;

    Map(size_t width, size_t height) : width(width), height(height), walls(new bool[width * height]) {};
    ~Map() {
        delete this->walls;
    };

    inline bool getWall(size_t x, size_t y);
    inline void setWall(size_t x, size_t y, bool value);
};

// inline methods should be in the header, apparently
inline bool Map::getWall(size_t x, size_t y) {
    return this->walls[y * width + x];
}

inline void Map::setWall(size_t x, size_t y, bool value) {
    this->walls[y * width + x] = value;
}