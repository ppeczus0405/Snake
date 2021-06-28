#ifndef TEXTURE_TYPE_H
#define TEXTURE_TYPE_H

#include <iostream>
#include <utility>

// Texture size config
constexpr int WINDOW_WIDTH = 1320;
constexpr int WINDOW_HEIGHT = 720;
constexpr int DEFAULT_TEXTURE_SIZE = 40;

constexpr int PLAY_BUTTON_WIDTH = 500;
constexpr int PLAY_BUTTON_HEIGHT = 125;

constexpr int QUIT_BUTTON_WIDTH = 500;
constexpr int QUIT_BUTTON_HEIGHT = 125;

constexpr int BACK_BUTTON_WIDTH = 500;
constexpr int BACK_BUTTON_HEIGHT = 125;

constexpr int RETRY_BUTTON_WIDTH = 500;
constexpr int RETRY_BUTTON_HEIGHT = 125;

constexpr int LOGO_WIDTH = 375;
constexpr int LOGO_HEIGHT = 375;
// Config END

const std::string PATH_BEGIN = "../Resources/";

enum TextureType{APPLE, BANANA, HDOWN, HLEFT, HRIGHT, HUP, STRAIGHTX, STRAIGHTY,
                 DLRU, DRLU, ULRD, URLD, TDOWN, TLEFT, TUP, TRIGHT, BACKGROUND, 
                 PLAY, PLAYHOVER, QUIT, QUITHOVER, RETRY, RETRYHOVER, BACKHOVER,
                 BACK, LOGO, NOTHING};


std::pair <std::string, std::pair <int, int> > getTexInfo(TextureType texType);

bool isCorner(TextureType type);

#endif // TEXTURE_TYPE_H