#pragma once

#include <SDL.h>
#include "LTexture.h"
#include "Ball.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

class Paddle
{
public:
	// dimensions
	static const int PADDLE_WIDTH = 10;
	static const int PADDLE_HEIGHT = 40;

	// max velocity
	static const int PADDLE_VELOCITY = 2;

	// inits vars
	Paddle(int posX, int posY);

	// moves up and checks collision with top wall
	void moveUp(const SDL_Rect& topWall);

	// moves down and checks collision with bottom wall
	void moveDown(const SDL_Rect& bottomWall);

	// determines and executes ai move based on ball position
	void executeAIMove(const Ball& ball);

	// shows the Paddle on screen
	// Currently using rect texture rendering to represent paddles, subject to change
	void render(/*const LTexture& gPaddleTexture*/);

	// checks collisions between rects
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

	// gets collider
	SDL_Rect getCollider() const;

	// set ball position (for restarts)
	void setPosition(int x, int y);

private:
	// x and y coords of the Paddle
	int mPosX;
	int mPosY;

	// Paddle's collision box
	SDL_Rect mCollider;
};
