#include "Paddle.h"

Paddle::Paddle()
{
	// set the inital position
	mPosX = 0;
	mPosY = 0;

	// set collision box dimension
	mCollider = { mPosX, mPosY, PADDLE_WIDTH, PADDLE_HEIGHT };
}

void Paddle::moveUp(const SDL_Rect& topWall)
{
	// move up/down
	mPosY += PADDLE_VELOCITY;
	mCollider.y = mPosY;

	// check collision or out of bounds
	if ((mPosY < 0) || checkCollision(mCollider, topWall))
	{
		// move back
		mPosY -= PADDLE_VELOCITY;
		mCollider.y = mPosY;
	}
}

void Paddle::moveDown(const SDL_Rect& bottomWall)
{
	// move down
	mPosY -= PADDLE_VELOCITY;
	mCollider.y = mPosY;

	// check collision or out of bounds
	if ((mPosY + PADDLE_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, /*bottom wall*/))
	{
		// move back
		mPosY += PADDLE_VELOCITY;
		mCollider.y = mPosY;
	}
}

void Paddle::render(SDL_Renderer* renderer, const LTexture& gPaddleTexture)
{
	// show the Paddle
	gPaddleTexture.render(renderer, mPosX, mPosY);
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
