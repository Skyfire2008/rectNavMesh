#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <filesystem>

#include "CivetServer.h"
#include "mapGen/mapGenerator.h"
#include "path/greedyDecomp.h"
#include "path/map.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    // FIXME: in debugger, argv[0] will be different
    // get the path to static html files: <folder with server.exe>/html
    auto exePath = fs::absolute(argv[0]).parent_path();
    auto htmlPath = (exePath / "html").string();

    const char* options[] = {
        "document_root", htmlPath.c_str(),
        "listening_ports", "8080",
        "index_files", "index.html",
        0};

    try {
        CivetServer server(options);

        while (true) {
            Sleep(1000);
        }

    } catch (const CivetException& e) {
        fprintf(stderr, "Error: %s\n", e.what());
    }

    return 0;

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
}