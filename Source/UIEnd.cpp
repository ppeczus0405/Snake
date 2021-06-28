#include "UIEnd.h"

UIEnd::UIEnd(int score) : backButton(BACK, BACK_POS), retryButton(RETRY, RETRY_POS), gamescore(score)
{}

void UIEnd::render(){
    backButton.render();
    retryButton.render();
}

void UIEnd::mouseMotionUpdate(Position const & mousePosition)
{
    ButtonAction retryAction = NORMAL;
    ButtonAction backAction = NORMAL;
    if(retryButton.isInside(mousePosition)){
        retryAction = HOVER;
    }
    if(backButton.isInside(mousePosition)){
        backAction = HOVER;
    }
    retryButton.changeState(retryAction);
    backButton.changeState(backAction);
}

void UIEnd::mouseClickUpdate(Position const & mousePosition)
{
    if(retryButton.isInside(mousePosition)){
        retryButton.changeState(PRESSED);
    }
    if(backButton.isInside(mousePosition)){
        backButton.changeState(PRESSED);
    }
}