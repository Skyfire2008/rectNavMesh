#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00  // This tells the compiler to target Windows 10
#endif
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <filesystem>

#include "httplib.h"
#include "mapGen/mapGenerator.h"
#include "path/greedyDecomp.h"
#include "path/map.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    auto exePath = fs::absolute(argv[0]).parent_path();
    auto htmlPath = exePath / "html";

    httplib::Server server;

    if (!server.set_mount_point("/", htmlPath.string())) {
        fprintf(stderr, "Could not open the folder %s\n", htmlPath.string().c_str());
        return 1;
    }

    server.listen("127.0.0.1", 5000);

    /*auto gen = RandomMapGenerator(0.5);
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
    }*/

    return 0;
}