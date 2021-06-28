#ifndef RENDERED_TEXTURE_H
#define RENDERED_TEXTURE_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureType.h"

inline int absRemainder(int x, int MODULO);

class Position
{
    public:
        static Position getRandomPosition();
        Position() = default;
        Position(int x, int y) : x(x), y(y) {move(0, 0);}
        Position(const Position &p) : x(p.x), y(p.y) {}
        Position(Position &&p) : x(p.x), y(p.y) {}
        ~Position() = default;
        int getX() const {return x;}
        int getY() const {return y;}
        void setX(int v) {x = v;}
        void setY(int v) {y = v;}
        void setXY(int v, int u) {x = v; y = u;}
        void move(int dx, int dy); // move by vector [dx, dy] including window size

        friend bool operator==(const Position &a, const Position &b);
        Position & operator=(const Position &p) {x = p.x; y=p.y; return *this;}
        Position & operator=(Position &&p){return *this = p;}
    private:
        int x = 0;
        int y = 0;
};

class RenderedTexture
{
    public:
        RenderedTexture() = default;
        RenderedTexture(TextureType texType, int x, int y);
        RenderedTexture(const RenderedTexture &rt);
        RenderedTexture(RenderedTexture &&rt);
        ~RenderedTexture();

        RenderedTexture & operator=(const RenderedTexture &rt);
        RenderedTexture & operator=(RenderedTexture &&rt);

        void move(int dx, int dy);
        void updatePosition(Position p);
        void changeTexture(TextureType texType);

        TextureType type;
        Position position;
        SDL_Texture * texture = nullptr;
        SDL_Rect destRect;
};

#endif // RENDERED_TEXTURE_H