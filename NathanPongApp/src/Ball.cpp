#include "Ball.h"
#include "Paddle.h"
#include <cmath>
#include "Utils.h"

Ball::Ball(int x, int y)
{
	posX = x;
	posY = y;
	
	xVel = 0;
	yVel = 0;
	velTotal = 0;

	ballCollider = { posX, posY, BALL_WIDTH, BALL_HEIGHT };
}

void Ball::move(double timeStep, const SDL_Rect& topWallCollider, const SDL_Rect& bottomWallCollider, const SDL_Rect& playerPaddleCollider, const SDL_Rect& aiPaddleCollider)
{
	// TODO change ball launch angle depending on where it hits the paddle
	// TODO implement increasing speed per paddle hit
	// TODO refactor calculating the velocities after ball bounces
	
	// attempt move X
	posX = Utils::preciseAdd(posX, xVel * timeStep);
	ballCollider.x = posX;

	// if ball struck a paddle
	if (checkCollision(ballCollider, playerPaddleCollider) || checkCollision(ballCollider, aiPaddleCollider))
	{
		// bounce ball against the paddle (only affects x position)

		// if ball is traveling to the left
		if (xVel < 0)
		{
			// posX is equal to the displacement past the paddle added onto the paddle width
			// ex: if ball started at posX = 15, posX was 7 after the move, and the paddle was at x = 10
			// ball moved 3 tiles past the paddle, and that displacement was translated into positive x (moving right)
			// final x position is 13
			posX = (Paddle::PADDLE_WIDTH - posX) + Paddle::PADDLE_WIDTH;
		}
		// ball is traveling to the right
		else if (xVel > 0)
		{
			// posX is off the screen to the right (posX>SCREEN_WIDTH)
			// bumper xPos = screen width - paddle width
			// displacement = posX - bumper
			// new posX = bumper - displacement
			posX = ((SCREEN_WIDTH - Paddle::PADDLE_WIDTH) + (posX + BALL_WIDTH - (SCREEN_WIDTH - Paddle::PADDLE_WIDTH)) - BALL_WIDTH);
		}

		// reverse x velocity
		xVel = -xVel;

		// re-align bounding box
		ballCollider.x = posX;
	}
	
	// attempt move Y
	posY = Utils::preciseAdd(posY,yVel * timeStep);
	ballCollider.y = posY;

	// if ball struck a wall
	if (checkCollision(ballCollider, topWallCollider) || checkCollision(ballCollider, bottomWallCollider))
	{
		// bounce ball against the wall (only affects y position)

		// if ball is traveling up
		if (yVel < 0)
		{
			// posY = displacement past top paddle added onto the paddle height
			// (ex: ball move 3 pixels past paddle, final position is 3 pixels below the paddle
			posY = (bottomWallCollider.h - posY) + bottomWallCollider.h;
		}
		// ball is traveling down
		if (yVel > 0)
		{
			// posY = displacement past bottom paddle subtracted from the paddle height
			// (ex: ball move 3 pixels past paddle, final position is 3 pixels above the paddle
			int finalPosition = (SCREEN_HEIGHT - bottomWallCollider.h) - (posY + BALL_HEIGHT - (SCREEN_HEIGHT - bottomWallCollider.h)) - BALL_HEIGHT;
			posY = static_cast<int>(round(finalPosition));
		}

		// reverse y velocity
		yVel = -yVel;

		// re-align bounding box;
		ballCollider.y = posY;
	}
}

int Ball::checkGoal(const SDL_Rect& leftGoal, const SDL_Rect& rightGoal)
{
	if (checkCollision(ballCollider, leftGoal))
	{
		return -1;
	}
	else if (checkCollision(ballCollider, rightGoal))
	{
		return 1;
	}
	
	return 0;
}

void Ball::render(const LTexture& ballTexture)
{
	ballTexture.render(posX, posY);
}

bool Ball::checkCollision(const SDL_Rect& a, const SDL_Rect& b)
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

void Ball::setPosition(int x, int y)
{
	posX = x;
	posY = y;

	// update collider
	ballCollider.x = posX;
	ballCollider.y = posY;
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
	yVel = calculateYVel(xVel);

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

double Ball::calculateYVel(double xVel)
{
	// pythagorean theorum :sunglas:
	return sqrt(velTotal * velTotal - xVel * xVel);
}
