#ifndef BUTTON_H
#define BUTTON_H

#include "GameObject.h"
#include "SDL2/SDL.h"
#include <functional>

class Game;
enum ButtonAction{NORMAL, HOVER, PRESSED};

class Button : public GameObject
{
    public:
        Button(TextureType const &texType, Position const &pos);
        ~Button();

        bool isInside(Position const &checkPos) const;
        void changeState(ButtonAction act);
        virtual void update() override;
    private:
        bool change = false;
        ButtonAction action = NORMAL;
        TextureType normalTex;
        TextureType hoverTex;

        std::function<void(Game &)> cleanFunc;
        std::function<void(Game &)> initFunc;
};

#endif // BUTTON_H