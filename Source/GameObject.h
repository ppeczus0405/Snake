#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <list>
#include <utility>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureMenager.h"

class Game;

class GameObject
{
    public:
        GameObject() = default;
        GameObject(std::vector < std::pair < TextureType, Position > > const &v);
        virtual ~GameObject();

        virtual void update();
        bool isColliding(GameObject * anotherGObject);
        void render();

    protected:
        std::list <RenderedTexture> objectState;
};

#endif //GAME_OBJECT_H