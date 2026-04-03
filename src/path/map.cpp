#include "map.h"

#include <stdio.h>

#include <charconv>

namespace path {

std::unique_ptr<Map> parseMap(size_t width, size_t height, std::string& hexString) {
    auto result = std::make_unique<Map>(width, height);

    size_t i = 0;                            // hexString index
    size_t j = 0;                            // data index
    for (; i < (width * height) / 4; i++) {  // don't read the character containing trailing bytes
        char c = hexString[i];
        int value = (c >= 'a') ? c - 'a' + 10 : c - '0';
        result->data[j++] = (value & 0b1000) != 0;
        result->data[j++] = (value & 0b0100) != 0;
        result->data[j++] = (value & 0b0010) != 0;
        result->data[j++] = (value & 0b0001) != 0;
    }

    // if there's an extra character containing leftover bits, covnert it, too
    int leftovers = (width * height) % 4;
    if (leftovers != 0) {
        char c = hexString[i];
        int value = (c >= 'a') ? c - 'a' + 10 : c - '0';
        int mask = 0b1000;
        for (int i = 0; i < leftovers; i++) {
            result->data[j++] = (value & mask) != 0;
            mask = mask >> 1;
        }
    }

    return result;
}

void printMap(Map& map) {
    for (size_t y = 0; y < map.height; y++) {
        for (size_t x = 0; x < map.width; x++) {
            auto isWall = map.get(x, y);
            std::fprintf(stdout, "%c", isWall ? '#' : ' ');
        }
        fprintf(stdout, "\n");
    }
}

}  // namespace path