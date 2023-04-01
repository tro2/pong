#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates a window
bool init();

// Loads media
bool loadMedia();

// Frees Media and shuts down SDL
void close();

SDL_Window* window = NULL;

SDL_Surface* screenSurface = NULL;

SDL_Surface* testImage = NULL;

int main(int, char**)
{
    // Start SDL and create window
    if (!init())
    {
        std::cout << "Failed to init!" << std::endl;
    }
    else
    {
        // Load Media
        if (!loadMedia())
        {
            std::cout << "Failed to load media!" << std::endl;
        }
        else
        {
            // apply image
            SDL_BlitSurface(testImage, NULL, screenSurface, NULL);

            SDL_UpdateWindowSurface(window);

            // Main loop flag
            bool quit = false;

            // Event handler
            SDL_Event e;

            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    switch (e.type)
                    {
                    case SDL_QUIT: quit = true;
                    }
                }
            }
        }
    }
    
    // cleanup and close
    close();

    return 0;
}

bool init()
{
    // flag
    bool success = true;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // create the window
        window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cout << "Window could not be created! Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            // set the screen surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool loadMedia()
{
    // load flag
    bool success = true;

    // load a splash image
    testImage = SDL_LoadBMP("test_image.bmp");
    if (testImage == NULL)
    {
        std::cout << "Unable to load image test_image! Error: " << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surfaces
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;

    SDL_FreeSurface(testImage);
    testImage = NULL;

    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}
