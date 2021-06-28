#include "Game.h"

InputMenager::InputMenager() : scene(BEGIN)
{}

void InputMenager::updateBegin(UIBegin * b){
    scene = BEGIN;
    begin = b;
}

void InputMenager::updateGame(Snake * s){
    scene = GAME;
    snake = s;
}

void InputMenager::updateEnd(UIEnd * x){
    scene = END;
    end = x;
}

void InputMenager::handleEvents()
{
    switch(scene)
    {
        case BEGIN:
            handleBegin();
            break;
        case GAME:
            handleGame();
            break;
        case END:
            handleEnd();
            break;
        default:
            break;
    }
}

void InputMenager::handleBegin()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                Game::game->endGame();
                break;
            case SDL_MOUSEMOTION:
                begin->mouseMotionUpdate(Position(e.motion.x, e.motion.y));
                break;
            case SDL_MOUSEBUTTONUP:
                begin->mouseClickUpdate(Position(e.motion.x, e.motion.y));
                break;
            default:
                break;
        }
    }
}

void InputMenager::handleGame()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                Game::game->endGame();
                break;
            case SDL_KEYDOWN:
                snake->setChangeDir(&e.key);
                break;
            default:
                break;
        }
    }
}

void InputMenager::handleEnd()
{
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                Game::game->endGame();
                break;
            case SDL_MOUSEMOTION:
                end->mouseMotionUpdate(Position(e.motion.x, e.motion.y));
                break;
            case SDL_MOUSEBUTTONUP:
                end->mouseClickUpdate(Position(e.motion.x, e.motion.y));
                break;
            default:
                break;
        }
    }
}