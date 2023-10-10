#pragma once

#include <SDL.h>

namespace Utils
{
    // VARIABLES ================================

    // FUNCTIONS ================================
    
    // generates random double between lowerBound and upperBound
    double randomDouble(double lowerBound, double upperBound);

    // generates random int between lowerBound and upperBound
    int randomInt(int lowerBound, int upperBound);

    // takes double and returns closest int
    int roundNearestPixel(double a);

    //checks collision between 2 SDL rects
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

    // calculates a in a^2 + b^2 = c^2
    double pythagCalcSide(double hyp, double side);
}
