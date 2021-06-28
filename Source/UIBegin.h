#ifndef BEGIN_UI_H
#define BEGIN_UI_H

#include "Button.h"
#include "SDL2/SDL.h"

const Position PLAY_POS = Position(410, 425);
const Position QUIT_POS = Position(410, 575);
const Position LOGO_POS = Position(485, 25);

class UIBegin
{
    public:
        UIBegin();
        void render();
        void mouseMotionUpdate(Position const & mousePosition);
        void mouseClickUpdate(Position const & mousePosition);
        Button playButton;
        Button quitButton;
        GameObject logo;
};


#endif //BEGIN_UI_H