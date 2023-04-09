#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "LTexture.h"
#include "LTimer.h"
#include "Paddle.h"
#include <sstream>

// window size
extern const int SCREEN_WIDTH = 720;
extern const int SCREEN_HEIGHT = 480;

// fps cap
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// Starts up SDL and creates a window
bool init(SDL_Window* gWindow, SDL_Renderer* gRenderer);

// Loads media
bool loadMedia();

// Frees Media and shuts down SDL
void close(SDL_Window* gWindow, SDL_Renderer* gRenderer);

int main(int, char**)
{
    // window
    SDL_Window* gWindow = NULL;

    // window renderer
    SDL_Renderer* gRenderer = NULL;
    
    // Start SDL and create window
    if (!init(gWindow, gRenderer))
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
            // FLAGS ==========================================
            // Main loop flag
            bool quit = false;

            // game started flag
            bool gameStarted = false;

            // game victory flag
            bool victory = false;

            // Event handler
            SDL_Event e;

            // OBJECTS ========================================
            // Player paddles
            Paddle playerPaddle;
            Paddle aiPaddle;

            // ball

            // top and bottom walls
            SDL_Rect topWall = { 0,0,SCREEN_WIDTH,40 };
            SDL_Rect bottomWall = { 0,SCREEN_HEIGHT-40,SCREEN_WIDTH,40 };

            // goal boxes


            // core loop
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }

                // Clear screen and prep for game logic
                SDL_RenderClear(gRenderer);

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                const Uint8* currentKeyboardState = SDL_GetKeyboardState(NULL);

                // if game needs to be restarted
                if (currentKeyboardState[SDLK_r])
                {
                    // restart flags
                    gameStarted = false;
                    victory = false;

                    // render game at the start
                }
                // game is stopped and needs to start
                else if (!gameStarted && !victory && currentKeyboardState[SDLK_SPACE])
                {
                    // start game
                    gameStarted = true;

                    // launch ball at random angle
                    
                }
                // game is in play
                else if (gameStarted && !victory)
                {
                    // look at player inputs
                    if (currentKeyboardState[SDLK_UP])
                    {
                        playerPaddle.moveUp(topWall);
                    }

                    if (currentKeyboardState[SDLK_DOWN])
                    {
                        playerPaddle.moveDown(bottomWall);
                    }

                    // ai inputs
                    // move ball and check for collisions

                }
                // game has finished
                else if (gameStarted && victory)
                {
                    // show "press r to restart" on top of current game
                }

                // handle inputs
                    // r - restart
                    // up and down arrow to move block
                    // spacebar to start

                // create ai "input"

                // physics
                    // move paddles
                    // check paddles
                        // if paddle is running into top or bottom walls
                    
                    // move ball
                    // check ball
                        // check if ball is touching paddle
                            // determine where paddle is touching, divide into paddle into thirds
                        // check if ball is in goal
                            // if yes, render success screen and pause all other physics



                // render
                    // top and bottom walls
                    // ball
                    // player bars

                // Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
    
    // cleanup and close
    close(gWindow, gRenderer);

    return 0;
}

bool init(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
    // flag
    bool success = true;

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // create the window
        gWindow = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            // create renderer for the main window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                // set init color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // init png loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not be created! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }

                // init SDL_ttf
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error:L %s\n", TTF_GetError());
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    // load flag
    bool success = true;

    // load ball

    // load player paddle

    // load ai paddle

    // load start text promt

    // load restart text prompt

    // load victory and restart text prompt

    return success;
}

void close(SDL_Window* gWindow, SDL_Renderer* gRenderer)
{
    // Deallocate textures


    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
