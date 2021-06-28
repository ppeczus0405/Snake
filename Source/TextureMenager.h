#ifndef TEXTURE_MENAGER_H
#define TEXTURE_MENAGER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "RenderedTexture.h"

class TextureMenager
{
    public:
        static TTF_Font * font;
        static SDL_Texture * LoadTexture(const char * filename);
        static void DisplayScore(std::string score, SDL_Rect renderRect);
        static void DisplayEnd(std::string score, SDL_Rect renderRect);
        static void Draw(RenderedTexture * tex);
};

#endif // TEXTURE_MENAGER_H