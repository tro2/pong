#pragma once

#include <SDL.h>

#include "LTexture.h"

struct AppContext {

	SDL_Window* gameWindow = nullptr;
	SDL_Renderer* gameRenderer = nullptr;

	const int SCREEN_WIDTH = 720;
	const int SCREEN_HEIGHT = 480;

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
