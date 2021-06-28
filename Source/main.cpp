#include "Game.h"

constexpr int ONE_SECOND = 1000;
constexpr int FPS = 11;
constexpr int FRAME_TIME = ONE_SECOND / FPS;

int main() {
    Game game("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    while(game.isRunning()){

        Uint32 frameDelay = SDL_GetTicks();

        game.handle_events();
        game.update();
        game.render();

        frameDelay = SDL_GetTicks() - frameDelay;

        if(frameDelay < FRAME_TIME)
        {
            SDL_Delay(FRAME_TIME - frameDelay);
        }
    }
    return 0;
}
