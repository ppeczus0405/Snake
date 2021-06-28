#include "RenderedTexture.h"
#include "TextureMenager.h"
#include <cstdlib>

int absRemainder(int x, int MODULO)
{
    int r = x % MODULO;
    if(r < 0)
        return r + MODULO;
    return r;
}

Position Position::getRandomPosition()
{
    int x = (rand() % WINDOW_WIDTH) * 40;
    int y = (rand() % WINDOW_HEIGHT) * 40;
    return Position(x, y);   
}

void Position::move(int dx, int dy)
{
    x = absRemainder(x + dx, WINDOW_WIDTH);
    y = absRemainder(y + dy, WINDOW_HEIGHT);
}

bool operator==(const Position &a, const Position &b)
{
    return a.getX() == b.getX() && a.getY() == b.getY();
}

RenderedTexture::RenderedTexture(TextureType texType, int x, int y) : position(Position(x, y))
{
    auto texinfo = getTexInfo(texType); // texinfo.first -- TEXPATH, texinfo.second -- {width, height}
    texture = TextureMenager::LoadTexture(texinfo.first.c_str());
    type = texType;

    // Destination Rectangle
    destRect.x = position.getX();
    destRect.y = position.getY();
    destRect.w = texinfo.second.first;
    destRect.h = texinfo.second.second;
}

RenderedTexture::RenderedTexture(const RenderedTexture &rt) :
                                type(rt.type), position(rt.position), destRect(rt.destRect)
{
    auto texinfo = getTexInfo(type);
    texture = TextureMenager::LoadTexture(texinfo.first.c_str());
}

RenderedTexture::RenderedTexture(RenderedTexture &&rt) :
                                type(std::move(rt.type)), position(std::move(rt.position)), destRect(std::move(rt.destRect))
{
    texture = rt.texture;
    rt.texture = nullptr;
    rt.type = NOTHING;
}

RenderedTexture& RenderedTexture::operator=(const RenderedTexture &rt)
{
    type = rt.type;
    destRect = rt.destRect; 
    position = rt.position;
    auto texinfo = getTexInfo(type);
    texture = TextureMenager::LoadTexture(texinfo.first.c_str());

    return *this;
}

RenderedTexture& RenderedTexture::operator=(RenderedTexture &&rt)
{
    type = std::move(rt.type);
    destRect = std::move(rt.destRect); 
    position = std::move(rt.position);
    texture = rt.texture;

    rt.texture = nullptr;
    rt.type = NOTHING;

    return *this;
}

void RenderedTexture::move(int dx, int dy)
{
    position.move(dx, dy);
    destRect.x = position.getX();
    destRect.y = position.getY();
}

void RenderedTexture::updatePosition(Position p)
{
    position.setXY(p.getX(), p.getY());
    move(0, 0);
}

void RenderedTexture::changeTexture(TextureType texType)
{
    SDL_DestroyTexture(texture);
    auto texinfo = getTexInfo(texType);
    texture = TextureMenager::LoadTexture(texinfo.first.c_str());
    type = texType;
}

RenderedTexture::~RenderedTexture()
{
    SDL_DestroyTexture(texture);
}