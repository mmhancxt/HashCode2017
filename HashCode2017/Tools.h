#pragma once

#include <random>

class Tools
{
public:
    // get uniformly distributed random number between min and max included
    static int GetUniformRandomNumber(int min, int max)
    {
        static std::random_device rdev;
        static std::default_random_engine engine(rdev());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(engine);
    }
};
