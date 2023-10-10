#pragma once

#include <random>

namespace Utils
{
    // VARIABLES ================================

    // FUNCTIONS ================================
    
    // generates random double between lowerBound and upperBound
    double randomDouble(double lowerBound, double upperBound);

    // generates random int between lowerBound and upperBound
    int randomInt(int lowerBound, int upperBound);

    // adds and properly rounds int a and double b
    int preciseAdd(int a, double b);
}
