#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mapGen/mapGenerator.h"
#include "path/greedyDecomp.h";
#include "path/map.h"

int main(int argc, char* args[]) {
    auto gen = RandomMapGenerator(0.5);
    auto map = gen.generate(10, 10);

    for (size_t y = 0; y < map->height; y++) {
        for (size_t x = 0; x < map->width; x++) {
            auto isWall = map->get(x, y);
            std::fprintf(stdout, "%c", isWall ? '#' : '.');
        }
        fprintf(stdout, "\n");
    }

    auto decomp = GreedyDecomp();
    auto rectangles = decomp.getRectangles(*map);
    for (size_t i = 0; i < rectangles->size(); i++) {
        auto rect = rectangles->at(i);
        fprintf(stdout, "x: %d, y: %d, width: %d, heigth: %d\n", rect.x, rect.y, rect.width, rect.height);
    }

    return 0;
}