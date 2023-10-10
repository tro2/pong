#pragma once

#include <SDL.h>
#include "LTexture.h"

// TODO (physics overhaul) refactor collision checking for objects into a physics manager
// Move the Goal Enum there
enum Goal
{
    AI,
    PLAYER,
    NONE
};

class Ball
{
public:
    // inits vars
    Ball(double posX, double posY);

    // moves ball and checks for collision with top/bottom wall and paddles
    void move(double timeStep, const SDL_Rect& topWallCollider, const SDL_Rect& bottomWallCollider
        , const SDL_Rect& playerPaddleCollider, const SDL_Rect& aiPaddleCollider);

    // checks if ball is in either goal
    Goal checkGoal(const SDL_Rect& leftGoal, const SDL_Rect& rightGoal);

    // set ball position (for restarts)
    void setPosition(double x, double y);

    // sets ball to random x and y velocity such that the launch angle
    // is between 45 and 135 degrees in either direction
    void launch();

    // gets coords
    double getX() const { return posX; }
    double getY() const { return posY; }

private:
    // ball position components
    double posX;
    double posY;

    // ball velocity components
    double xVel;
    double yVel;

    // ball total velocity
    double velTotal;

    // collider
    SDL_Rect ballCollider;
};
