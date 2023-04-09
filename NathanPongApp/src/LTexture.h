#pragma once

#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

// Wrapper class for SDL Textures to make colorkeying easier
class LTexture
{
public:
	LTexture();

	~LTexture();

	// loads the image at specified path
	bool loadFromFile(SDL_Renderer* renderer, std::string path);

	// loads text string into a texture with the given color
	bool loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor);

	// dealloc texture
	void free();

	// set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// set blending
	void setBlendMode(SDL_BlendMode blending);

	// set alpha modulation
	void setAlpha(Uint8 alpha);

	// render texture using the global renderer at the given point, optional clip for sprite sheet
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL) const;

	// get dimensions
	int getWidth() const;
	int getHeight() const;

private:
	// the underlying texture
	SDL_Texture* mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};
