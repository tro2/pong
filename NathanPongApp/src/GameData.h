#pragma once

#include <SDL.h>

#include "LTexture.h"

struct AppContext {

    SDL_Window* gameWindow = nullptr;
    SDL_Renderer* gameRenderer = nullptr;

    const double SCREEN_WIDTH = 720.0;
    const double SCREEN_HEIGHT = 480.0;

    const double Pixels_Per_Unit = 1.0;

};

struct GameData {

    // Game Window
    const double SCREEN_WIDTH = 720.0;
    const double SCREEN_HEIGHT = 480.0;

    // Ball
    const double BALL_WIDTH = 10.0;
    const double BALL_HEIGHT = 10.0;

    const double BALL_VELOCITY = 200.0;

    // Paddle
    const double PADDLE_WIDTH = 15.0;
    const double PADDLE_HEIGHT = 80.0;

    const double PADDLE_VELOCITY = 150.0;

    // Walls

    // Goals
};

struct Textures {

    // text textures
    LTexture spacebarStartTextTexture;
    LTexture victoryTextTexture;
    LTexture restartTextTexture;
    LTexture scoreTextTexture;

    // object textures
    LTexture ballTexture;

};
