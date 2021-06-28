#ifndef FRUIT_H
#define FRUIT_H

#include "Snake.h"
#include "RenderedTexture.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <cstdlib>
#include <climits>
#include <vector>
#include <chrono>

constexpr int APPLE_TIME = INT_MAX;
constexpr int BANANA_TIME_MIN = 3500;
constexpr int BANANA_TIME_MAX = 7000;

constexpr int APPLE_SCORE = 1;
constexpr int BANANA_SCORE = 3;

class Fruit : public GameObject
{
    public:
        Fruit(Snake * gObject, TextureType const &texType, std::vector <Position> const &banned);
        ~Fruit();
        virtual void update() override;
        bool isAlive();
        bool isEndTime();
        TextureType getFruitType();
        Position getPosition();
    private:
        const std::chrono::time_point<std::chrono::steady_clock> tBegin;
        bool alive = true;
        Snake * snake = nullptr;
        int time = APPLE_TIME;
        int score = APPLE_SCORE;
};

#endif // FRUIT_H