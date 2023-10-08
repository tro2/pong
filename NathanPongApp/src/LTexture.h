#pragma once

#include <string>
#include <iostream>

#include <SDL.h>

// TODO make this class stupid and think about access

// Wrapper class for SDL Textures to make colorkeying easier
class LTexture
{
public:
	LTexture();

	~LTexture();

	// dealloc texture
	void free();

	// get texture
	SDL_Texture* getMTexture() const { return mTexture; }

	// get dimensions
	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; };

	// sets texture pointer
	void setMTexture(SDL_Texture* texture) { mTexture = texture; }

	// sets dimensions
	void setWidth(int w) { mWidth = w; }
	void setHeight(int h) { mHeight = h; }

private:
	// the underlying texture
	SDL_Texture* mTexture;

	// Image dimensions
	int mWidth;
	int mHeight;
};
