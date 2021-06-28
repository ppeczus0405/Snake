#include "TextureType.h"

std::pair <std::string, std::pair <int, int> > getTexInfo(TextureType texType)
{
    switch(texType)
    {
        case APPLE:
            return {PATH_BEGIN + "apple.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case BANANA:
            return {PATH_BEGIN + "banana.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case HDOWN:
            return {PATH_BEGIN + "headDown.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case HLEFT:
            return {PATH_BEGIN + "headLeft.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case HRIGHT:
            return {PATH_BEGIN + "headRight.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case HUP:
            return {PATH_BEGIN + "headUp.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case STRAIGHTX:
            return {PATH_BEGIN + "straightX.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}}; 
        case STRAIGHTY:
            return {PATH_BEGIN + "straightY.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case DLRU:
            return {PATH_BEGIN + "downLeft_rightUp.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case DRLU:
            return {PATH_BEGIN + "downRight_leftUp.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case ULRD:
            return {PATH_BEGIN + "upLeft_rightDown.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case URLD:
            return {PATH_BEGIN + "upRight_leftDown.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case TDOWN:
            return {PATH_BEGIN + "tailDown.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case TLEFT:
            return {PATH_BEGIN + "tailLeft.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case TRIGHT:
            return {PATH_BEGIN + "tailRight.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case TUP:
            return {PATH_BEGIN + "tailUp.png", {DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE}};
        case BACKGROUND:
            return {PATH_BEGIN + "background.jpg", {WINDOW_WIDTH, WINDOW_HEIGHT}};
        case PLAY:
            return {PATH_BEGIN + "play.png", {PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT}};
        case PLAYHOVER:
            return {PATH_BEGIN + "playhover.png", {PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT}};
        case QUIT:
            return {PATH_BEGIN + "quit.png", {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT}};
        case QUITHOVER:
            return {PATH_BEGIN + "quithover.png", {QUIT_BUTTON_WIDTH, QUIT_BUTTON_HEIGHT}};
        case BACK:
            return {PATH_BEGIN + "back.png", {BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT}};
        case BACKHOVER:
            return {PATH_BEGIN + "backhover.png", {BACK_BUTTON_WIDTH, BACK_BUTTON_HEIGHT}};
        case RETRY:
            return {PATH_BEGIN + "retry.png", {RETRY_BUTTON_WIDTH, RETRY_BUTTON_HEIGHT}};
        case RETRYHOVER:
            return {PATH_BEGIN + "retryhover.png", {RETRY_BUTTON_WIDTH, RETRY_BUTTON_HEIGHT}};
        case LOGO:
            return {PATH_BEGIN + "logo.png", {LOGO_WIDTH, LOGO_HEIGHT}};
        default:
            return {"INVALID PATH", {-1, -1}};
    }
}

bool isCorner(TextureType texType)
{
    return texType == DLRU || texType == DRLU || texType == ULRD || texType == URLD;
}