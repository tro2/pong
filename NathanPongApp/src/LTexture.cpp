#include "LTexture.h"
#include <SDL_image.h>

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

void LTexture::free()
{
    // if texture exists
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

