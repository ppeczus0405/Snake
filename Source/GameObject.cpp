#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(std::vector < std::pair < TextureType, Position > > const &v)
{   
    for(auto &x : v){
        objectState.push_back(RenderedTexture(x.first, x.second.getX(), x.second.getY()));
    }
}

void GameObject::render()
{
    for(auto &x : objectState){
        TextureMenager::Draw(&x);
    }
}

GameObject::~GameObject()
{
    for(auto &x : objectState){
        SDL_DestroyTexture(x.texture);
    }
}

void GameObject::update()
{
    std::cout << "GameObject Updated" << std::endl;
}

bool GameObject::isColliding(GameObject * anotherGObject)
{
    auto aPos = objectState.begin()->position;

    for(auto &b: anotherGObject->objectState){
        if(aPos == b.position)
            return true;
    }

    return false;
}