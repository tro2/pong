#include "Paddle.h"

Paddle::Paddle(int posX, int posY)
{
	// set the inital position
	mPosX = posX;
	mPosY = posY;

	// set collision box dimension
	mCollider = { mPosX, mPosY, PADDLE_WIDTH, PADDLE_HEIGHT };
}

void Paddle::moveUp(double timeStep, const SDL_Rect& topWall)
{
	// move up/down
	mPosY = add(mPosY, -PADDLE_VELOCITY * timeStep);
	mCollider.y = mPosY;

	// check collision or out of bounds
	if ((mPosY < 0) || checkCollision(mCollider, topWall))
	{
		// move back
		mPosY = add(mPosY, PADDLE_VELOCITY * timeStep);
		mCollider.y = mPosY;
	}
}

void Paddle::moveDown(double timeStep, const SDL_Rect& bottomWall)
{
	// move down
	mPosY = add(mPosY, PADDLE_VELOCITY * timeStep);
	mCollider.y = mPosY;

	// check collision or out of bounds
	if ((mPosY + PADDLE_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, bottomWall))
	{
		// move back
		mPosY = add(mPosY, -PADDLE_VELOCITY * timeStep);
		mCollider.y = mPosY;
	}
}

void Paddle::executeAIMove(const Ball& ball)
{
	// TODO code AI behavior
}

void Paddle::render(/*const LTexture& gPaddleTexture*/)
{
	// show the Paddle
	// gPaddleTexture.render(mPosX, mPosY);

	// simple rect based rendering
	SDL_RenderFillRect(gRenderer, &mCollider);
}

bool Paddle::checkCollision(const SDL_Rect& a, const SDL_Rect& b)
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

SDL_Rect Paddle::getCollider() const
{
	return mCollider;
}

void Paddle::setPosition(int x, int y)
{
	mPosX = x;
	mPosY = y;

	// update collider as well
	mCollider.x = mPosX;
	mCollider.y = mPosY;
}

int Paddle::add(int a, double b)
{
	double preciseA = a;
	preciseA += b;

	return static_cast<int>(round(preciseA));
}
