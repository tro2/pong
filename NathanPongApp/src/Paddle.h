#pragma once

#include <SDL.h>
#include "LTexture.h"
#include "Ball.h"

class Paddle
{
public:
    // inits vars
    Paddle(double posX, double posY, double width, double height);

    // moves up and checks collision with top wall
    void moveUp(double timeStep, const SDL_Rect& topWall);

    // moves down and checks collision with bottom wall
    void moveDown(double timeStep, const SDL_Rect& bottomWall);

    // determines and executes ai move based on ball position
    void executeAIMove(const Ball& ball, double timeStep, const SDL_Rect& topWall
        , const SDL_Rect& bottomWall);

    // gets collider
    SDL_Rect getCollider() const;

    // set ball position (for restarts)
    void setPosition(double x, double y);

private:
    // x and y coords of the Paddle
    double posX;
    double posY;

    // dimensions
    double width;
    double height;

    // Paddle's collision box
    SDL_Rect mCollider;
};
