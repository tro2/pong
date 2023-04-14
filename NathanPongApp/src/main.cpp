#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "LTexture.h"
#include "LTimer.h"
#include "Paddle.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

// ==============================================
// GLOBAL VARIABLES

// window size
extern const int SCREEN_WIDTH = 720;
extern const int SCREEN_HEIGHT = 480;

// window
SDL_Window* gWindow = NULL;

// window renderer
extern SDL_Renderer* gRenderer = NULL;

// text font
TTF_Font* gFontRegular;
TTF_Font* gFontBoldLarge;

// text color / wall color
SDL_Color blackColor = { 0, 0, 0, 0 };

// test text texture
LTexture textTexture;
LTexture ballTexture;
LTexture victoryTextTexture;
LTexture restartTextTexture;
LTexture scoreTextTexture;

// ==============================================
// FUNCTIONS

// Starts up SDL and creates a window
bool init();

// Loads media
bool loadMedia();

// Frees Media and shuts down SDL
void close();

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
            const int WALL_HEIGHT = 40;
            const int GOAL_BOX_WIDTH = 7;
            const int TARGET_GOALS = 3;
            
            // FLAGS ============================
            // Main loop flag
            bool quit = false;

            // game started flag
            bool gameStarted = false;

            // game victory flag
            bool victory = false;

            // OBJECTS ==========================

            // Player paddles
            Paddle playerPaddle(0, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
            Paddle aiPaddle(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);

            // create ball in center of screen
            Ball gBall((SCREEN_WIDTH - Ball::BALL_WIDTH) / 2, (SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

            // top and bottom walls
            SDL_Rect topWall = { 0, 0, SCREEN_WIDTH, WALL_HEIGHT };
            SDL_Rect bottomWall = { 0, SCREEN_HEIGHT - WALL_HEIGHT, SCREEN_WIDTH, WALL_HEIGHT };

            // goal boxes
            SDL_Rect leftGoal = { 0, 0, GOAL_BOX_WIDTH, SCREEN_HEIGHT };
            SDL_Rect rightGoal = { SCREEN_WIDTH- GOAL_BOX_WIDTH, 0, GOAL_BOX_WIDTH, SCREEN_HEIGHT };

            // OTHER ============================
            
            // Score
            int aiScore = 0;
            int playerScore = 0;

            // Score Text
            std::stringstream scoreText;
            scoreText << "Player: 0 AI: 0";

            // Delta timer
            LTimer deltaTimer;
            double timeStep = 0;

            // Event handler
            SDL_Event e;

            // ==============================
                // GAME LOOP

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
                            // if yes, increment goal tick and reset game to start next round

                // render
                    // top and bottom walls
                    // ball
                    // player bars

            // core loop
            while (!quit)
            {
                deltaTimer.start();
                
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
                if (currentKeyboardState[SDL_SCANCODE_R])
                {
                    // restart flags
                    gameStarted = false;
                    victory = false;

                    // reset all positions
                    playerPaddle.setPosition(0, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    aiPaddle.setPosition(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    gBall.setPosition((SCREEN_WIDTH - Paddle::PADDLE_WIDTH) / 2, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);

                    // restart goal count
                    aiScore = 0;
                    playerScore = 0;
                }
                // game is stopped and needs to start
                else if (!gameStarted && !victory && currentKeyboardState[SDL_SCANCODE_SPACE])
                {
                    // start game
                    gameStarted = true;

                    gBall.launch();

                }
                // game is in play
                if (gameStarted && !victory)
                {
                    // look at player inputs
                    if (currentKeyboardState[SDL_SCANCODE_UP])
                    {
                        playerPaddle.moveUp(timeStep, topWall);
                    }

                    if (currentKeyboardState[SDL_SCANCODE_DOWN])
                    {
                        playerPaddle.moveDown(timeStep, bottomWall);
                    }

                    // ai inputs
                    aiPaddle.executeAIMove(gBall, timeStep, topWall, bottomWall);

                    // move ball and check for collisions
                    gBall.move(timeStep, topWall, bottomWall, playerPaddle.getCollider(), aiPaddle.getCollider());

                    // check score achieved
                    switch (gBall.checkGoal(leftGoal, rightGoal))
                    {
                        case -1:
                        {
                            aiScore++;
                            if (aiScore == TARGET_GOALS)
                            {
                                victoryTextTexture.loadFromRenderedText(gFontBoldLarge, "AI Wins!", blackColor);
                                victory = true;
                            }

                            // increment score counter texture
                            scoreText.str("");
                            scoreText << "Player: " << playerScore << " AI: " << aiScore;
                            scoreTextTexture.loadFromRenderedText(gFontRegular, scoreText.str().c_str(), blackColor);

                            // restart game
                            // restart flags
                            gameStarted = false;

                            // reset all positions
                            playerPaddle.setPosition(0, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                            aiPaddle.setPosition(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                            gBall.setPosition((SCREEN_WIDTH - Ball::BALL_WIDTH) / 2, (SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

                            break;
                        }
                        case 1:
                        {
                            playerScore++;
                            if (playerScore == TARGET_GOALS)
                            {
                                victoryTextTexture.loadFromRenderedText(gFontBoldLarge, "Player Wins!", blackColor);
                                victory = true;
                            }

                            // increment score counter texture
                            scoreText.str("");
                            scoreText << "Player: " << playerScore << " AI: " << aiScore;
                            scoreTextTexture.loadFromRenderedText(gFontRegular, scoreText.str().c_str(), blackColor);

                            // restart game
                            // restart flags
                            gameStarted = false;

                            // reset all positions
                            playerPaddle.setPosition(0, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                            aiPaddle.setPosition(SCREEN_WIDTH - Paddle::PADDLE_WIDTH, (SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                            gBall.setPosition((SCREEN_WIDTH - Ball::BALL_WIDTH) / 2, (SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

                            break;
                        }
                        default: break;
                    }
                }

                // render
                // ball
                gBall.render(ballTexture);

                // paddles
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 0);
                playerPaddle.render();

                SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
                aiPaddle.render();

                // top and bottom wall
                SDL_SetRenderDrawColor(gRenderer, 0, 125, 0, 0);
                SDL_RenderFillRect(gRenderer, &topWall);
                SDL_RenderFillRect(gRenderer, &bottomWall);

                // score
                scoreTextTexture.render(2, 2);

                // specific case rendering
                if (!victory && !gameStarted)
                {
                    textTexture.render((SCREEN_WIDTH - textTexture.getWidth()) / 2, (SCREEN_HEIGHT - textTexture.getHeight()) / 2 - 30);
                }

                if (victory)
                {
                    victoryTextTexture.render((SCREEN_WIDTH - textTexture.getWidth()) / 2, (SCREEN_HEIGHT - textTexture.getHeight()) / 2 - 50);
                    restartTextTexture.render((SCREEN_WIDTH - textTexture.getWidth()) / 2, (SCREEN_HEIGHT - textTexture.getHeight()) / 2);
                }

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Update screen
                SDL_RenderPresent(gRenderer);

                timeStep = deltaTimer.getTicks() / 1000.0;
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

    gFontRegular = TTF_OpenFont("arial.ttf", 14);
    if (gFontRegular == NULL)
    {
        printf("Unable to load regular font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }

    gFontBoldLarge = TTF_OpenFont("arial.ttf", 20);
    if (gFontBoldLarge == NULL)
    {
        printf("Unable to load large bold font! TTF Error: %s\n", TTF_GetError());
        success = false;
    }
    // set font to bold
    TTF_SetFontStyle(gFontBoldLarge, TTF_STYLE_BOLD);

    if (!textTexture.loadFromRenderedText(gFontRegular, "Press Spacebar to start", blackColor))
    {
        printf("Unable to load test text!\n");
        success = false;
    }

    if (!victoryTextTexture.loadFromRenderedText(gFontRegular, "Victory!", blackColor))
    {
        printf("Unable to load victory text!\n");
        success = false;
    }

    if (!restartTextTexture.loadFromRenderedText(gFontRegular, "Press 'R' to restart...", blackColor))
    {
            printf("Unable to load restart text!\n");
            success = false;
    }

    if (!scoreTextTexture.loadFromRenderedText(gFontRegular, "Player: 0 AI:0", blackColor))
    {
        printf("Unable to load score text!\n");
        success = false;
    }

    if (!ballTexture.loadFromFile("dot.bmp"))
    {
        printf("Unable to load ball texture!\n");
        success = false;
    }

    return success;
}

void close()
{
    // Deallocate textures
    textTexture.free();
    victoryTextTexture.free();
    ballTexture.free();
    restartTextTexture.free();
    scoreTextTexture.free();


    // Dealloc Fonts
    TTF_CloseFont(gFontRegular);
    TTF_CloseFont(gFontBoldLarge);

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
