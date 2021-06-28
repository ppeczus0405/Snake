#ifndef END_UI_H
#define END_UI_H

#include "Button.h"
#include "SDL2/SDL.h"

const Position RETRY_POS = Position(148, 548);
const Position BACK_POS = Position(673, 548);

class UIEnd
{
    public:
        UIEnd(int score);
        void render();
        void mouseMotionUpdate(Position const & mousePosition);
        void mouseClickUpdate(Position const & mousePosition);
        Button backButton;
        Button retryButton;
        int gamescore;
};

#endif //BEGIN_UI_H