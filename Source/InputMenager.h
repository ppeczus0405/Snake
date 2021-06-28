#ifndef INPUT_MENAGER_H
#define INPUT_MENAGER_H

#include "SDL2/SDL.h"
#include "Snake.h"
#include "UIBegin.h"
#include "UIEnd.h"

class Game;
enum GameScene : short;

class InputMenager
{
    public:
        InputMenager();
        void handleEvents();

        void updateBegin(UIBegin * b);
        void updateGame(Snake * s);
        void updateEnd(UIEnd * x);
    private:
        void handleBegin();
        void handleGame();
        void handleEnd();

        GameScene scene;
        UIBegin *begin = nullptr;
        Snake *snake = nullptr;
        UIEnd *end = nullptr;
        SDL_Event e;
};

#endif // INPUT_MENAGER_H