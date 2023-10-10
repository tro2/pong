#include "Utils.h"

#include <cmath>
#include <random>

double Utils::randomDouble(double lowerBound, double upperBound)
{
    // random device for randomization functions
    static std::random_device rand;

    // randomization engine
    static std::default_random_engine eng(rand());
    
    std::uniform_real_distribution<double> distr(lowerBound, upperBound);

    return distr(eng);
}

int Utils::randomInt(int lowerBound, int upperBound)
{
    // random device for randomization functions
    static std::random_device rand;

    // randomization engine
    static std::default_random_engine eng(rand());
    
    std::uniform_int_distribution<int> distr(lowerBound, upperBound);

    return distr(eng);
}

int Utils::roundNearestPixel(double a)
{
    return static_cast<int>(round(a));
}

bool Utils::checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    // the sides to check collisions
    int leftA;
    int rightA;
    int topA;
    int bottomA;

    int leftB;
    int rightB;
    int topB;
    int bottomB;

    // Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    // Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    // if horizontal bounds do not overlap
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    // if vertical bounds do not overlap
    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    // both horizontal and vertical bounds overlap
    return true;
}

double Utils::pythagCalcSide(double hyp, double side)
{
    return sqrt(hyp * hyp - side * side);
}
