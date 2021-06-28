#include "UIBegin.h"

UIBegin::UIBegin() : playButton(PLAY, PLAY_POS), quitButton(QUIT, QUIT_POS), 
                     logo(std::vector<std::pair<TextureType, Position>>(1, {LOGO, LOGO_POS}))
{}

void UIBegin::render()
{
    playButton.render();
    quitButton.render();
    logo.render();
}

void UIBegin::mouseMotionUpdate(Position const & mousePosition)
{
    ButtonAction playAction = NORMAL;
    ButtonAction quitAction = NORMAL;
    if(playButton.isInside(mousePosition)){
        playAction = HOVER;
    }
    if(quitButton.isInside(mousePosition)){
        quitAction = HOVER;
    }
    playButton.changeState(playAction);
    quitButton.changeState(quitAction);
}

void UIBegin::mouseClickUpdate(Position const & mousePosition)
{
    if(playButton.isInside(mousePosition)){
        playButton.changeState(PRESSED);
    }
    if(quitButton.isInside(mousePosition)){
        quitButton.changeState(PRESSED);
    }
}