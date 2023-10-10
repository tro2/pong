#pragma once

#include <SDL.h>
#include "LTexture.h"

// TODO these are placeholder variables until collisions are abstracted into a game logic manager
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

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
    // ball characteristics
    const static int BALL_WIDTH = 10;
    const static int BALL_HEIGHT = 10;

    // the starting total velocity in pixels per second
    static constexpr double START_VELOCITY = 200;

    // inits vars
    Ball(int posX, int posY);

    // calculates the appropriate Y velocity to maintain MAX_VELOCITY 
    double calculateYVel(double xVel);

    // moves ball and checks for collision with top/bottom wall and paddles
    void move(double timeStep, const SDL_Rect& topWallCollider, const SDL_Rect& bottomWallCollider
        , const SDL_Rect& playerPaddleCollider, const SDL_Rect& aiPaddleCollider);

    // checks if ball is in either goal
    Goal checkGoal(const SDL_Rect& leftGoal, const SDL_Rect& rightGoal);

    // helper function to check collision between ball and wall
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

    // set ball position (for restarts)
    void setPosition(int x, int y);

    // sets ball to random x and y velocity such that the launch angle
    // is between 45 and 135 degrees in either direction
    void launch();

    // gets coords
    int getX() const { return posX; }
    int getY() const { return posY; }

private:
    // ball position components
    int posX;
    int posY;

    // ball velocity components
    double xVel;
    double yVel;

    // ball total velocity
    double velTotal;

    // collider
    SDL_Rect ballCollider;
};
