#pragma once

#include <SDL.h>
#include "LTexture.h"

class Ball
{
public:
	// ball characteristics
	const static int BALL_WIDTH = 10;
	const static int BALL_HEIGHT = 10;

	// the maximum allowed total velocity
	static constexpr double MAX_VELOCITY = 2.0;

	// inits vars
	Ball(int posX, int posY);

	// calculates the appropriate Y velocity to maintain MAX_VELOCITY 
	double calculateYVel(double xVel);

	// moves ball and checks for collision with top/bottom wall and paddles
	void move(const SDL_Rect& topWallCollider, const SDL_Rect& bottomWallCollider, const SDL_Rect& playerPaddleCollider, const SDL_Rect& aiPaddleCollider);

	// checks if ball is in either goal
	// returns -1 if in left goal
	// returns 0 if not in a goal
	// returns 1 if in right goal
	// TODO Make this an Enum
	int checkGoal(const SDL_Rect& leftGoal, const SDL_Rect& rightGoal);

	// shows the ball on screen
	void render(const LTexture& ballTexture);

	// helper function to check collision between ball and wall
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

	// set ball position (for restarts)
	void setPosition(int x, int y);

	// sets ball to random x and y velocity such that the launch angle is between 45 and 135 degrees in either direction
	void launch();

private:
	// ball position components
	int posX;
	int posY;

	// ball velocity components
	double xVel;
	double yVel;

	SDL_Rect ballCollider;

	
	// helper function to add double velocity b to int a and ensure proper rounding
	int addVelocity(int a, double b);
};
