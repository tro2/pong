#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameData.h"
#include "LTexture.h"

// Renderer class abstracts SDL_Renderer
class RenderManager
{
public:

    // Fonts
    TTF_Font* gFontRegular;
    TTF_Font* gFontBoldLarge;

    // Colors
    const SDL_Color black = { 0,0,0,0 };
    const SDL_Color red = { 255,0,0,0 } ;
    const SDL_Color blue = { 0,0,255,0 };
    const SDL_Color green = { 0,125,0,0 };

    RenderManager();

    ~RenderManager() {};

    // unloads all textures and app context
    void close(AppContext& appContext, Textures& textures) const;

    // inits game renderer and game window
    bool init(AppContext& appContext) const;
    
    // loads fonts and returns true if sucessful, false otherwise
    bool loadFonts();

    // loads the image at specified path into given LTexture
    bool loadFromFile(LTexture& texture, std::string path, AppContext& appContext) const;

    // loads text string into a texture with the given color into given LTexture
    bool loadFromRenderedText(LTexture& texture, TTF_Font* font, std::string textureText
        , SDL_Color textColor, AppContext& appContext) const;

    // loads game textures into Textures&
    bool loadTextures(AppContext& appContext, Textures& textures) const;

    // render given texture using the renderer at the given point, optional clip for sprite sheet
    void renderTexture(const LTexture& lTexture, int x, int y, AppContext& appContext
        , SDL_Rect* clip = nullptr) const;

    // TODO Temp function to render rects until texture is made or I decide what to do
    void renderRect(const SDL_Rect& rect, const SDL_Color& color, AppContext& appContext);

};
