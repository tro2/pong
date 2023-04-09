#include "LTexture.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

LTexture::LTexture()
{
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	// dealloc
	free();
}

bool LTexture::loadFromFile(SDL_Renderer* renderer, std::string path)
{
	// remove possible preexisting texture
	free();

	// first create a surface, then convert
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load iamge " << path << "! SDL_image error: " << IMG_GetError() << std::endl;
	}
	else
	{
		// color key the image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		// convert surface to texture
		mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (mTexture == NULL)
		{
			std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		// get rid of old surface
		SDL_FreeSurface(loadedSurface);
	}

	// return success
	return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, std::string textureText, SDL_Color textColor)
{
	// remove possible preexisting texture
	free();

	// render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		// convert surface to texture
		mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		// get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	// return success
	return mTexture != NULL;
}

void LTexture::free()
{
	// if texture exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(mTexture, red, blue, green);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip) const
{
	// define rendering space and render
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	// set clip rendering rect
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() const
{
	return mWidth;
}

int LTexture::getHeight() const
{
	return mHeight;
}
