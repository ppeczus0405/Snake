#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <iterator>
#include <utility>
#include <cstdlib>
#include <utility>
#include "SDL2/SDL.h"
#include "GameObject.h"

constexpr int SBEGIN_X = 17;
constexpr int SBEGIN_Y = 14;

enum Direction {UP, DOWN, LEFT, RIGHT, NONE};

class Snake : public GameObject
{
    public:
        Snake();
        ~Snake();
        virtual void update() override;
        inline bool isEnd(){return end;}
        void setChangeDir(SDL_KeyboardEvent *key);
        void addScore(int s);
        int getScore();
        void setLonger();

    private:
        bool end = false;
        bool longer = false;
        int score = 0;
        
        
        std::tuple<int, int, TextureType> getMove();
        bool isOver();
        bool goForwardHead();
        void goForwardTail();
        void goForward();
        void changeDirection();


        Direction currentDir;
        Direction toChange;
};

#endif // SNAKE_H