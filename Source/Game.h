#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "RenderedTexture.h"
#include "InputMenager.h"
#include "Fruit.h"
#include "Snake.h"
#include "UIBegin.h"
#include "UIEnd.h"

// Settings responsible for fruits on game scene
constexpr int MAX_APPLES = 3;
constexpr int MAX_BANANAS = 2;

constexpr int APPLE_PROB = 1500;
constexpr int BANANA_PROB = 100;
constexpr int WAIT_BEFORE_PLAY = 1300;
constexpr int WAIT_BEFORE_END_MENU = 1500;

// Settings for score string for end and game scene
constexpr int GAME_SCORE_STRING_X = 16;
constexpr int GAME_SCORE_STRING_Y = 0;
constexpr int GAME_SCORE_STRING_HEIGHT = 100;
constexpr int GAME_SCORE_STRING_WIDTH = 200;

constexpr int END_SCORE_STRING_X = 210;
constexpr int END_SCORE_STRING_Y = 0;
constexpr int END_SCORE_STRING_HEIGHT = 350;
constexpr int END_SCORE_STRING_WIDTH = 900;

enum GameScene : short {BEGIN, GAME, END};

class Game
{
    public:
        Game(const char * title, int x, int y, int width, int height, bool fulscreen);
        ~Game();
        
        //Main game loop functions
        void handle_events();
        void update();
        void render();
        bool isRunning();

        //Game end function
        void endGame();

        // Cleaning function for display another game scene
        void cleanBegin();
        void cleanGame();
        void cleanEnd();

        // Initialization functions preparing scene before display
        void initBegin();
        void initGame();
        void initEnd();

        static SDL_Renderer *renderer;
        static Game * game;
        static int apples;
        static int bananas;

    private:
        bool addFruit(TextureType fruit);

        // Rendering functions for each scene
        void renderBegin();
        void renderGame();
        void renderEnd();

        // Update functions for each scene
        void updateBegin();
        void updateGame();
        void updateEnd();

        bool running = true;
        bool wait = false; // wait before start play

        SDL_Window *window = nullptr;
        RenderedTexture bg;

        SDL_Rect gameStringRect;
        SDL_Rect endStringRect;

        Snake *snake;
        std::list < std::unique_ptr <Fruit> > fruits;

        GameScene actScene = BEGIN;
        UIBegin *beginUI = nullptr;
        UIEnd *endUI = nullptr;
        InputMenager input;
};

#endif // GAME_H