#include "../util/util.h"
#include "mapGenerator.h"

RandomMapGenerator::RandomMapGenerator(float prob) : prob(prob) {}

std::unique_ptr<Map> RandomMapGenerator::generate(size_t width, size_t height) {
    auto result = std::make_unique<Map>(width, height);

    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            auto isWall = util::random() < prob;
            result->set(x, y, isWall);
        }
    }

    return result;
}