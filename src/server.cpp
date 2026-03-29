#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mapGen/mapGenerator.h"
#include "path/map.h"

int main(int argc, char* args[]) {
    auto gen = RandomMapGenerator(0.9);
    auto map = gen.generate(10, 10);

    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            auto isWall = map->getWall(x, y);
            std::fprintf(stdout, "%c", isWall ? '#' : '.');
        }
        fprintf(stdout, "\n");
    }

    return 0;
}