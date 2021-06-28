#include "Button.h"
#include "Game.h"

Button::Button(TextureType const &texType, Position const &pos)
{
    objectState.push_back(RenderedTexture(texType, pos.getX(), pos.getY()));
    normalTex = texType;
    switch(texType)
    {
        case PLAY:
            cleanFunc = &Game::cleanBegin;
            initFunc = &Game::initGame;
            hoverTex = PLAYHOVER;
            break;
        case QUIT:
            cleanFunc = &Game::cleanBegin;
            initFunc = &Game::endGame;
            hoverTex = QUITHOVER;
            break;
        case BACK:
            cleanFunc = &Game::cleanEnd;
            initFunc = &Game::initBegin;
            hoverTex = BACKHOVER;
            break;
        case RETRY:
            cleanFunc = &Game::cleanEnd;
            initFunc = &Game::initGame;
            hoverTex = RETRYHOVER;
            break;
        default:
            break;
    }
}

void Button::changeState(ButtonAction act)
{
    // The same state as actual
    if(act == action) return;

    change = true;
    action = act;
}

bool Button::isInside(Position const &checkPos) const
{
    const auto &buttonPos = objectState.back().position;
    const auto &buttonWidth = objectState.back().destRect.w;
    const auto &buttonHeight = objectState.back().destRect.h;

    return (checkPos.getX() >= buttonPos.getX()) && (checkPos.getX() <= buttonPos.getX() + buttonWidth) &&
           (checkPos.getY() >= buttonPos.getY()) && (checkPos.getY() <= buttonPos.getY() + buttonHeight);
}

void Button::update()
{
    //Without any change
    if(!change) return;
    
    change = false;
    switch(action)
    {
        case NORMAL:
            objectState.back().changeTexture(normalTex);
            break;
        case HOVER:
            objectState.back().changeTexture(hoverTex);
            break;
        case PRESSED:
            initFunc(*Game::game);
            cleanFunc(*Game::game);
            break;
        default:
            break;
    }
}

Button::~Button()
{
    SDL_DestroyTexture(objectState.back().texture);
    objectState.pop_back();
}