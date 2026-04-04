#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <filesystem>
#include <string>

#include "CivetServer.h"
#include "json.hpp"
#include "mapGen/mapGenerator.h"
#include "path/greedyDecomp.h"
#include "path/map.h"

namespace fs = std::filesystem;
using json = nlohmann::json;

// TODO: move reading the request body into a separate function
class NavMeshHandler : public CivetHandler {
    bool handlePost(CivetServer* server, struct mg_connection* conn) {
        auto reqInfo = mg_get_request_info(conn);

        if (reqInfo->content_length <= 0) {
            fprintf(stderr, "Error: content length not set\n");
            mg_send_http_error(conn, 411, "Content length required");
            return true;
        }

        std::string body;
        body.reserve(reqInfo->content_length);

        // use the buffer to read the whole payload
        bool connActive = true;
        char buffer[1024];
        long long readBytes = 0;
        while (readBytes < reqInfo->content_length) {
            size_t len = reqInfo->content_length - readBytes;
            if (len > sizeof(buffer)) {
                len = sizeof(buffer);
            }

            int lastRead = mg_read(conn, buffer, len);
            if (lastRead <= 0) {
                fprintf(stderr, "Error: Could not read data or connection closed\n");
                connActive = false;
                break;
            }

            body.append(buffer);

            readBytes += lastRead;
        }

        fprintf(stdout, "%s\n", body.c_str());

        // convert the json to a map
        auto bodyJson = json::parse(body);
        auto level = bodyJson["level"];
        int width = level["width"].get<int>();
        int height = level["height"].get<int>();
        std::string hexString = level["tiles"].get<std::string>();

        auto map = path::parseMap(width, height, hexString);
        printMap(*map);

        // calculate the navmesh
        if (bodyJson["algorithm"].get<int>() == 0) {
            auto decomp = GreedyDecomp();
            auto rectangles = decomp.getRectangles(*map);
            json result = *rectangles;
            std::string jsonString = result.dump();

            mg_send_http_ok(conn, "application/json", jsonString.length());
            mg_write(conn, jsonString.c_str(), jsonString.length());

        } else {
            fprintf(stderr, "Error: Navmesh algorithm %d is not implemented\n", bodyJson["algorithm"].get<int>());
        }

        return true;
    }
};

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
        NavMeshHandler handler;
        server.addHandler("/navmesh", handler);

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