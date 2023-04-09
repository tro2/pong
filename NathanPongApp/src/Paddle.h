#pragma once

#include <SDL.h>
#include "LTexture.h"

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
	Paddle();

	// moves up and checks collision with top wall
	void moveUp(const SDL_Rect& topWall);

	// moves down and checks collision with bottom wall
	void moveDown(const SDL_Rect& bottomWall);

	// shows the Paddle on screen
	void render(SDL_Renderer* renderer, const LTexture& gPaddleTexture);

	bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

private:
	// x and y coords of the Paddle
	int mPosX;
	int mPosY;

	// Paddle's collision box
	SDL_Rect mCollider;
};
