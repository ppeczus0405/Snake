#include "TextureMenager.h"
#include "Game.h"

TTF_Font * TextureMenager::font = nullptr;

const SDL_Color green = {64, 125, 65, 0};
const SDL_Color red = {252, 78, 3, 0};


SDL_Texture* TextureMenager::LoadTexture(const char * filename){
    SDL_Surface *surf = IMG_Load(filename);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    SDL_FreeSurface(surf);

    return tex;
}

void TextureMenager::DisplayScore(std::string score, SDL_Rect renderRect)
{
    std::string text = "Score: " + score;
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), green);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);
    
    constexpr int oneDigitPxCorrection = 8;
    constexpr int DigitPx = 29;
    int widthCorrection = ((int)score.size() - 1) * DigitPx;
    for(int i = 0; i < (int)score.size(); i++){
        if(score[i] == '1')
            widthCorrection -= oneDigitPxCorrection;
    }
    renderRect.w += widthCorrection;

    SDL_RenderCopy(Game::renderer, tex, NULL, &renderRect);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void TextureMenager::DisplayEnd(std::string score, SDL_Rect renderRect)
{
    SDL_Surface *surf = TTF_RenderText_Solid(font, "GAME OVER!", red);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, surf);

    SDL_RenderCopy(Game::renderer, tex, NULL, &renderRect);

    renderRect.h = GAME_SCORE_STRING_HEIGHT * 2;
    renderRect.w = GAME_SCORE_STRING_WIDTH * 2;
    renderRect.x = (WINDOW_WIDTH - renderRect.w) / 2;
    renderRect.y += END_SCORE_STRING_HEIGHT - 35;

    DisplayScore(score, renderRect);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void TextureMenager::Draw(RenderedTexture * tex)
{
    SDL_RenderCopy(Game::renderer, tex->texture, NULL, &(tex->destRect));
}
