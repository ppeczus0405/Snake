#include "Fruit.h"
#include "Game.h"

Fruit::Fruit(Snake * s, TextureType const &texType, std::vector <Position> const &banned) : tBegin(std::chrono::steady_clock::now()), snake(s)
{
    Position pos = Position::getRandomPosition();
    objectState.push_back(RenderedTexture(texType, pos.getX(), pos.getY()));
    while(isColliding(snake) || std::find(banned.begin(), banned.end(), pos) != banned.end()){
        pos = Position::getRandomPosition();
        objectState.begin()->updatePosition(pos);
    }
    if(texType == BANANA){
        time = BANANA_TIME_MIN + rand() % (BANANA_TIME_MAX - BANANA_TIME_MIN + 1);
        score = BANANA_SCORE;
        Game::bananas++;
    }
    else{
        Game::apples++;
    }
}

void Fruit::update()
{
    if(snake->isColliding(this)){
        alive = false;
        snake->addScore(score);
    }
}

bool Fruit::isAlive()
{
    return alive;
}

bool Fruit::isEndTime()
{
    auto tEnd = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tBegin);
    return static_cast<int>(duration.count()) > time;
}

TextureType Fruit::getFruitType()
{
    return objectState.begin()->type;
}

Position Fruit::getPosition()
{
    return objectState.begin()->position;
}

Fruit::~Fruit()
{
    switch (objectState.back().type)
    {
        case APPLE:
            Game::apples--;
            break;
        default:
            Game::bananas--;
            break;
    }
    SDL_DestroyTexture(objectState.back().texture);
    objectState.pop_back();
}