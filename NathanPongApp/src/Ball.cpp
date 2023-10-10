#include "Ball.h"
#include "Paddle.h"
#include <cmath>
#include "Utils.h"
#include "Renderer.h"

Ball::Ball(double x, double y)
{
    posX = x;
    posY = y;
    
    xVel = 0;
    yVel = 0;
    velTotal = 0;

    ballCollider = { Utils::roundNearestPixel(posX)
        , Utils::roundNearestPixel(posY)
        , Utils::roundNearestPixel(BALL_WIDTH)
        , Utils::roundNearestPixel(BALL_HEIGHT) };
}

void Ball::move(double timeStep, const SDL_Rect& topWallCollider
    , const SDL_Rect& bottomWallCollider, const SDL_Rect& playerPaddleCollider
    , const SDL_Rect& aiPaddleCollider)
{
    // TODO (physics overhaul) change ball launch angle depending on 
    // where it hits the paddle
    // TODO (physics overhaul) implement increasing speed per paddle hit
    // TODO (physics overhaul) refactor calculating the velocities after 
    // ball bounces into a free function
    
    // attempt move X
    posX += xVel * timeStep;
    ballCollider.x = Utils::roundNearestPixel(posX);

    // if ball struck a paddle
    if (Utils::checkCollision(ballCollider, playerPaddleCollider) 
        || Utils::checkCollision(ballCollider, aiPaddleCollider))
    {
        // bounce ball against the paddle (only affects x position)

        double PADDLE_WIDTH = 15.0;

        // if ball is traveling to the left
        if (xVel < 0.0)
        {
            // posX is equal to the displacement past the paddle added onto the paddle width
            // ex: if ball started at posX = 15, posX was 7 after the move
            // and the paddle was at x = 10
            // ball moved 3 tiles past the paddle
            // and that displacement was translated into positive x (moving right)
            // final x position is 13
            posX = (PADDLE_WIDTH - posX) + PADDLE_WIDTH;
        }
        // ball is traveling to the right
        else if (xVel > 0.0)
        {
            // posX is off the screen to the right (posX>SCREEN_WIDTH)
            // bumper xPos = screen width - paddle width
            // displacement = posX - bumper
            // new posX = bumper - displacement
            posX = ((SCREEN_WIDTH - PADDLE_WIDTH) + (posX + BALL_WIDTH
                - (SCREEN_WIDTH - PADDLE_WIDTH)) - BALL_WIDTH);
        }

        // reverse x velocity
        xVel = -xVel;

        // re-align bounding box
        ballCollider.x = Utils::roundNearestPixel(posX);
    }
    
    // attempt move Y
    posY += yVel * timeStep;
    ballCollider.y = Utils::roundNearestPixel(posY);

    // if ball struck a wall
    if (Utils::checkCollision(ballCollider, topWallCollider) 
        || Utils::checkCollision(ballCollider, bottomWallCollider))
    {
        // bounce ball against the wall (only affects y position)

        // if ball is traveling up
        if (yVel < 0)
        {
            // posY = displacement past top paddle added onto the paddle height
            // (ex: ball move 3 pixels past paddle, final position is 3 pixels below the paddle
            posY = (static_cast<double>(bottomWallCollider.h) - posY)
                + static_cast<double>(bottomWallCollider.h);
        }
        // ball is traveling down
        if (yVel > 0)
        {
            // posY = displacement past bottom paddle subtracted from the paddle height
            // (ex: ball move 3 pixels past paddle, final position is 3 pixels above the paddle
            double finalPosition = (SCREEN_HEIGHT - static_cast<double>(bottomWallCollider.h))
                - (posY + BALL_HEIGHT 
                    - (SCREEN_HEIGHT - static_cast<double>(bottomWallCollider.h)))
                - BALL_HEIGHT;
            posY = finalPosition;
        }

        // reverse y velocity
        yVel = -yVel;

        // re-align bounding box;
        ballCollider.y = Utils::roundNearestPixel(posY);
    }
}

Goal Ball::checkGoal(const SDL_Rect& leftGoal, const SDL_Rect& rightGoal)
{
    if (Utils::checkCollision(ballCollider, leftGoal))
    {
        return Goal::AI;
    }
    else if (Utils::checkCollision(ballCollider, rightGoal))
    {
        return Goal::PLAYER;
    }
    
    return Goal::NONE;
}

void Ball::setPosition(double x, double y)
{
    posX = x;
    posY = y;

    // update collider
    ballCollider.x = Utils::roundNearestPixel(posX);
    ballCollider.y = Utils::roundNearestPixel(posY);
}

void Ball::launch()
{
    // set target velocity
    velTotal = START_VELOCITY;

    // define bounds for random vel generator, and ensures ball isn't fired directly at paddle
    double upperBound = START_VELOCITY * 7/8;
    double lowerBound = START_VELOCITY * sqrt(2) / 2;

    // calculate velocities
    xVel = Utils::randomDouble(lowerBound, upperBound);
    yVel = Utils::pythagCalcSide(START_VELOCITY, xVel);

    // randomize direction
    if (Utils::randomInt(0,1))
    {
        xVel = -xVel;
    }

    if (Utils::randomInt(0,1))
    {
        yVel = -yVel;
    }
}
