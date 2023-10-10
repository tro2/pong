#include "Paddle.h"

#include "Utils.h"
#include "GameData.h"

Paddle::Paddle(double posX, double posY, double width, double height)
{
    // set the inital position
    posX = posX;
    posY = posY;

    // sets size
    width = width;
    height = height;

    // set collision box dimension
    mCollider = { Utils::roundNearestPixel(posX)
        , Utils::roundNearestPixel(posY)
        , Utils::roundNearestPixel(width)
        , Utils::roundNearestPixel(height) };
}

void Paddle::moveUp(double timeStep, const SDL_Rect& topWall)
{
    // move up/down
    posY += -PADDLE_VELOCITY * timeStep;
    mCollider.y = Utils::roundNearestPixel(posY);

    // check collision or out of bounds
    if ((posY < 0) || Utils::checkCollision(mCollider, topWall))
    {
        // move back
        posY += PADDLE_VELOCITY * timeStep;
        mCollider.y = Utils::roundNearestPixel(posY);
    }
}

void Paddle::moveDown(double timeStep, const SDL_Rect& bottomWall)
{
    // move down
    posY += PADDLE_VELOCITY * timeStep;
    mCollider.y = Utils::roundNearestPixel(posY);

    // check collision or out of bounds
    // HACK only checking collision with bottom wall
    // doesn't account for the paddle moving completely clear of the bottom wall
    if (Utils::checkCollision(mCollider, bottomWall))
    {
        // move back
        posY += -PADDLE_VELOCITY * timeStep;
        mCollider.y = Utils::roundNearestPixel(posY);
    }
}

void Paddle::executeAIMove(const Ball& ball, double timeStep, const SDL_Rect& topWall
    , const SDL_Rect& bottomWall)
{
    // if ball is above
    if (ball.getY() < this->posY)
    {
        this->moveUp(timeStep, topWall);
    }
    // if ball is below
    else if (ball.getY() > this->posY + PADDLE_HEIGHT)
    {
        this->moveDown(timeStep, bottomWall);
    }
}

SDL_Rect Paddle::getCollider() const
{
    return mCollider;
}

void Paddle::setPosition(double x, double y)
{
    posX = x;
    posY = y;

    // update collider as well
    mCollider.x = Utils::roundNearestPixel(posX);
    mCollider.y = Utils::roundNearestPixel(posY);
}
