#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <ctime>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "LTexture.h"
#include "LTimer.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Logger.h"


// ==============================================
// GLOBAL VARIABLES

// TODO refactor global variables into structs
// textures can be attached to objects
// colors can go into renderer class
// fonts can go into renderer class
// text textures should be abstracted into a new class

// TODO (rendering overhaul) Abstract gRenderer into a class
// create Paddle textures or an RenderRect Function

// ==============================================
// FUNCTIONS

// Inits SDL
bool init();

// Frees Media and shuts down SDL
void close(AppContext& appContext, RenderManager& renderManager, Textures& textures);

int main(int, char**)
{
    AppContext appContext;

    RenderManager renderManager;

    Textures gameTextures;

    // Start SDL
    if (!init())
    {
        std::cout << "Failed to init SDL!" << std::endl;
        return -1;
    }

    // Create RenderManager and Window
    if (!renderManager.init(appContext))
    {
        std::cout << "Failed to load app context!" << std::endl;
        return -1;
    }

    // Load fonts
    if (!renderManager.loadFonts())
    {
        std::cout << "Failed to load fonts!" << std::endl;
        return -1;
    }

    // Load textures
    if (!renderManager.loadTextures(appContext, gameTextures))
    {
        std::cout << "Failed to load textures!" << std::endl;
        return -1;
    }

    // Start game loop
    const int WALL_HEIGHT = 40;
    const int GOAL_BOX_WIDTH = 7;
    const int TARGET_GOALS = 3;

    // FLAGS ============================
    // Main loop flag
    bool quit = false;

    /*
    // game started flag
    bool gameStarted = false;

    // game victory flag
    bool victory = false;
    */

    enum GameState
    {
        READY,
        IN_GAME,
        VICTORY,
    };

    // game state flag
    GameState gameState = READY;

    // OBJECTS ==========================

    // Player paddles
    Paddle playerPaddle(0, (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
    Paddle aiPaddle(appContext.SCREEN_WIDTH - Paddle::PADDLE_WIDTH
        , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);

    // create ball in center of screen
    Ball gBall((appContext.SCREEN_WIDTH - Ball::BALL_WIDTH) / 2
        , (appContext.SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

    // top and bottom walls
    SDL_Rect topWall = { 0, 0, appContext.SCREEN_WIDTH, WALL_HEIGHT};
    SDL_Rect bottomWall = { 0, appContext.SCREEN_HEIGHT - WALL_HEIGHT
        , appContext.SCREEN_WIDTH, WALL_HEIGHT };

    // goal boxes
    SDL_Rect leftGoal = { 0, 0, GOAL_BOX_WIDTH, appContext.SCREEN_HEIGHT };
    SDL_Rect rightGoal = { appContext.SCREEN_WIDTH - GOAL_BOX_WIDTH, 0
        , GOAL_BOX_WIDTH, appContext.SCREEN_HEIGHT };

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
        SDL_RenderClear(appContext.gameRenderer);

        SDL_SetRenderDrawColor(appContext.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        const Uint8* currentKeyboardState = SDL_GetKeyboardState(nullptr);

        // if game needs to be restarted
        if (currentKeyboardState[SDL_SCANCODE_R])
        {
            // restart flags
            gameState = GameState::READY;

            // reset all positions
            playerPaddle.setPosition(0
                , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
            aiPaddle.setPosition(appContext.SCREEN_WIDTH - Paddle::PADDLE_WIDTH
                , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
            gBall.setPosition((appContext.SCREEN_WIDTH - Paddle::PADDLE_WIDTH) / 2
                , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);

            // restart goal count
            aiScore = 0;
            playerScore = 0;
        }
        // game is stopped and needs to start
        else if (gameState == READY && currentKeyboardState[SDL_SCANCODE_SPACE])
        {
            // start game
            gameState = IN_GAME;

            gBall.launch();

        }
        // game is in play
        if (gameState == IN_GAME)
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
            gBall.move(timeStep, topWall, bottomWall
                , playerPaddle.getCollider()
                , aiPaddle.getCollider());

            // check score achieved
            switch (gBall.checkGoal(leftGoal, rightGoal))
            {
                case Goal::AI:
                {
                    aiScore++;
                    if (aiScore == TARGET_GOALS)
                    {
                        renderManager.loadFromRenderedText(gameTextures.victoryTextTexture
                            , renderManager.gFontBoldLarge, "AI Wins!", renderManager.black
                            , appContext);
                        gameState = GameState::VICTORY;
                    }
                    else
                    {
                        gameState = GameState::READY;
                    }

                    // increment score counter texture
                    scoreText.str("");
                    scoreText << "Player: " << playerScore << " AI: " << aiScore;
                    renderManager.loadFromRenderedText(gameTextures.scoreTextTexture
                        , renderManager.gFontRegular, scoreText.str().c_str(), renderManager.black
                        , appContext);

                    // restart game
                    // TODO refactor reset code into a free function

                    // reset all positions
                    playerPaddle.setPosition(0
                        , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    aiPaddle.setPosition(appContext.SCREEN_WIDTH - Paddle::PADDLE_WIDTH
                        , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    gBall.setPosition((appContext.SCREEN_WIDTH - Ball::BALL_WIDTH) / 2
                        , (appContext.SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

                    break;
                }
                case Goal::PLAYER:
                {
                    playerScore++;
                    if (playerScore == TARGET_GOALS)
                    {
                        renderManager.loadFromRenderedText(gameTextures.victoryTextTexture
                            , renderManager.gFontBoldLarge, "Player Wins!", renderManager.black
                            , appContext);
                        gameState = GameState::VICTORY;
                    }
                    else
                    {
                        // game should continue
                        gameState = GameState::READY;
                    }

                    // increment score counter texture
                    scoreText.str("");
                    scoreText << "Player: " << playerScore << " AI: " << aiScore;
                    renderManager.loadFromRenderedText(gameTextures.scoreTextTexture
                        , renderManager.gFontRegular, scoreText.str().c_str(), renderManager.black
                        , appContext);

                    // restart game

                    // reset all positions
                    playerPaddle.setPosition(0
                        , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    aiPaddle.setPosition(appContext.SCREEN_WIDTH - Paddle::PADDLE_WIDTH
                        , (appContext.SCREEN_HEIGHT - Paddle::PADDLE_HEIGHT) / 2);
                    gBall.setPosition((appContext.SCREEN_WIDTH - Ball::BALL_WIDTH) / 2
                        , (appContext.SCREEN_HEIGHT - Ball::BALL_HEIGHT) / 2);

                    break;
                }
                default: break;
            }
        }

        // render
        // ball
        renderManager.renderTexture(gameTextures.ballTexture, gBall.getX(), gBall.getY()
            , appContext, nullptr);

        // paddles
        renderManager.renderRect(playerPaddle.getCollider(), renderManager.blue, appContext);
        renderManager.renderRect(aiPaddle.getCollider(), renderManager.red, appContext);

        // top and bottom wall
        renderManager.renderRect(topWall, renderManager.green, appContext);
        renderManager.renderRect(bottomWall, renderManager.green, appContext);

        // score
        renderManager.renderTexture(gameTextures.scoreTextTexture, 2, 2
            , appContext, nullptr);

        // specific case rendering
        if (gameState == READY)
        {
            renderManager.renderTexture(gameTextures.spacebarStartTextTexture,
                (appContext.SCREEN_WIDTH - gameTextures.spacebarStartTextTexture.getWidth())
                / 2,
                (appContext.SCREEN_HEIGHT - gameTextures.spacebarStartTextTexture.getHeight())
                / 2 - 30,
                appContext, nullptr);
        }

        if (gameState == VICTORY)
        {
            renderManager.renderTexture(gameTextures.victoryTextTexture,
                (appContext.SCREEN_WIDTH - gameTextures.spacebarStartTextTexture.getWidth()) 
                / 2,
                (appContext.SCREEN_HEIGHT - gameTextures.spacebarStartTextTexture.getHeight()) 
                / 2 - 50
                , appContext, nullptr);
            renderManager.renderTexture(gameTextures.restartTextTexture,
                (appContext.SCREEN_WIDTH - gameTextures.spacebarStartTextTexture.getWidth()) / 2,
                (appContext.SCREEN_HEIGHT - gameTextures.spacebarStartTextTexture.getHeight()) / 2
                , appContext, nullptr);
        }

        SDL_SetRenderDrawColor(appContext.gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Update screen
        SDL_RenderPresent(appContext.gameRenderer);

        timeStep = deltaTimer.getTicks() / 1000.0;
    }

    // cleanup and close
    close(appContext, renderManager, gameTextures);

    return 0;
    
}

bool init()
{
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized! SDL Error: " << SDL_GetError() 
            << std::endl;
        return false;
    }

    // init png loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not be created! SDL_image Error: " << IMG_GetError() 
            << std::endl;
        return false;
    }

    // init SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() 
            << std::endl;
        return false;
    }

    return true;
}

void close(AppContext& appContext, RenderManager& renderManager, Textures& textures)
{
    // clean up renderer
    renderManager.close(appContext, textures);

    // Quit SDL subsystems
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
