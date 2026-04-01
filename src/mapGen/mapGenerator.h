#pragma once

#include <memory>
#include <random>

#include "../path/map.h"

using namespace path;

class MapGenerator {
   public:
    virtual std::unique_ptr<Map> generate(size_t width, size_t height) = 0;
    virtual ~MapGenerator() = default;
};

class RandomMapGenerator : public MapGenerator {
   public:
    /**
     * Probability that the tile will be set to wall
     */
    float prob;

    RandomMapGenerator(float prob);
    std::unique_ptr<Map> generate(size_t width, size_t height);
};