#include "util.h"

#include <iostream>
#include <random>

namespace util {
double random() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);

    return dis(gen);
}
}  // namespace util
