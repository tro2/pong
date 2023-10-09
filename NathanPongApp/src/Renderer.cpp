#include "Renderer.h"

#include <iostream>
#include <SDL_image.h>

Renderer::Renderer()
{
    // Fonts
    TTF_Font* gFontRegular = nullptr;
    TTF_Font* gFontBoldLarge = nullptr;

}

void Renderer::close(AppContext& appContext, Textures& textures) const
{
    // Deallocate textures
    textures.spacebarStartTextTexture.free();
    textures.victoryTextTexture.free();
    textures.restartTextTexture.free();
    textures.scoreTextTexture.free();

    textures.ballTexture.free();

    // Dealloc Fonts
    TTF_CloseFont(gFontRegular);
    TTF_CloseFont(gFontBoldLarge);

    SDL_DestroyRenderer(appContext.gameRenderer);
    appContext.gameRenderer = nullptr;

    // Destroy window
    SDL_DestroyWindow(appContext.gameWindow);
    appContext.gameWindow = nullptr;
}

bool Renderer::init(AppContext& appContext) const
{
    // create the window
    appContext.gameWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED
        , SDL_WINDOWPOS_UNDEFINED, appContext.SCREEN_WIDTH, appContext.SCREEN_HEIGHT
        , SDL_WINDOW_SHOWN);
    if (appContext.gameWindow == nullptr)
    {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer for the main window
    appContext.gameRenderer = SDL_CreateRenderer(appContext.gameWindow, -1
        , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (appContext.gameRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Renderer::loadFonts()
{
    // load flag
    bool success = true;

    gFontRegular = TTF_OpenFont("arial.ttf", 14);
    if (gFontRegular == nullptr)
    {
        printf("Unable to load regular font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }

    gFontBoldLarge = TTF_OpenFont("arial.ttf", 20);
    if (gFontBoldLarge == nullptr)
    {
        printf("Unable to load large bold font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }

    // set font to bold
    TTF_SetFontStyle(gFontBoldLarge, TTF_STYLE_BOLD);

    return success;
}

bool Renderer::loadFromFile(LTexture& lTexture, std::string path, AppContext& appContext) const
{
    // remove possible preexisting texture
    lTexture.free();

    // first create a surface, then convert
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load iamge " << path << "! SDL_image error: " << IMG_GetError() 
            << std::endl;
    }
    else
    {
        // color key the image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        // convert surface to texture
        lTexture.setMTexture(SDL_CreateTextureFromSurface(appContext.gameRenderer, loadedSurface));
        if (lTexture.getMTexture() == nullptr)
        {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " 
                << SDL_GetError() << std::endl;
        }
        else
        {
            lTexture.setWidth(loadedSurface->w);
            lTexture.setHeight(loadedSurface->h);
        }

        // get rid of old surface
        SDL_FreeSurface(loadedSurface);
    }

    // return success
    return lTexture.getMTexture() != nullptr;
}

bool Renderer::loadFromRenderedText(LTexture& lTexture, TTF_Font* font, std::string textureText
    , SDL_Color textColor, AppContext& appContext) const
{
    // remove possible preexisting texture
    lTexture.free();

    // render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if (textSurface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // convert surface to texture
        lTexture.setMTexture(SDL_CreateTextureFromSurface(appContext.gameRenderer, textSurface));
        if (lTexture.getMTexture() == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            lTexture.setWidth(textSurface->w);
            lTexture.setHeight(textSurface->h);
        }

        // get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    // return success
    return lTexture.getMTexture() != nullptr;
}

bool Renderer::loadTextures(AppContext& appContext, Textures& textures) const
{
    // load flag
    bool success = true;

    // text textures
    if (!loadFromRenderedText(textures.spacebarStartTextTexture, gFontRegular
        , "Press Spacebar to start", black, appContext))
    {
        printf("Unable to load test text!\n");
        success = false;
    }

    if (!loadFromRenderedText(textures.victoryTextTexture, gFontRegular, "Victory!", black
        , appContext))
    {
        printf("Unable to load victory text!\n");
        success = false;
    }

    if (!loadFromRenderedText(textures.restartTextTexture, gFontRegular, "Press 'R' to restart..."
        , black, appContext))
    {
        printf("Unable to load restart text!\n");
        success = false;
    }

    if (!loadFromRenderedText(textures.scoreTextTexture, gFontRegular, "Player: 0 AI: 0", black
        , appContext))
    {
        printf("Unable to load score text!\n");
        success = false;
    }

    // game textures
    if (!loadFromFile(textures.ballTexture, "dot.bmp", appContext))
    {
        printf("Unable to load ball texture!\n");
        success = false;
    }

    return success;
}

void Renderer::renderTexture(const LTexture& lTexture, int x, int y, AppContext& appContext
    , SDL_Rect* clip) const
{
    // define rendering space and render
    SDL_Rect renderQuad = { x, y, lTexture.getWidth(), lTexture.getHeight() };

    // set clip rendering rect
    if (clip != nullptr)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(appContext.gameRenderer, lTexture.getMTexture(), clip, &renderQuad);
}

void Renderer::renderPaddle(const SDL_Rect& rect, AppContext& appContext)
{
    SDL_RenderFillRect(appContext.gameRenderer, &rect);
}
