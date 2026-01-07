#pragma once
#include <random>

class Random {
    static std::mt19937& engine() {
        static std::random_device rd;
        static std::mt19937 eng(rd());
        return eng;
    }
public:
    static float uniform01() {
        static std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        return dist(engine());
    }
    static int randInt(int minInclusive, int maxInclusive) {
        std::uniform_int_distribution<int> dist(minInclusive, maxInclusive);
        return dist(engine());
    }
};
