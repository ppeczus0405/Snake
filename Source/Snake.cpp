#include "Snake.h"


Snake::Snake()
{
    objectState.push_back(RenderedTexture(HUP, SBEGIN_X * DEFAULT_TEXTURE_SIZE, (SBEGIN_Y - 3) * DEFAULT_TEXTURE_SIZE));
    objectState.push_back(RenderedTexture(STRAIGHTY, SBEGIN_X * DEFAULT_TEXTURE_SIZE, (SBEGIN_Y - 2) * DEFAULT_TEXTURE_SIZE));
    objectState.push_back(RenderedTexture(STRAIGHTY, SBEGIN_X * DEFAULT_TEXTURE_SIZE, (SBEGIN_Y - 1) * DEFAULT_TEXTURE_SIZE));
    objectState.push_back(RenderedTexture(TUP, SBEGIN_X * DEFAULT_TEXTURE_SIZE, SBEGIN_Y * DEFAULT_TEXTURE_SIZE));

    currentDir = UP;
}

std::tuple<int, int, TextureType> Snake::getMove()
{
    std::pair <int, int> delta = {DEFAULT_TEXTURE_SIZE, 0};
    TextureType moveTexture = STRAIGHTX;

    switch(currentDir)
    {
        case LEFT:
            delta = {-DEFAULT_TEXTURE_SIZE, 0};
            break;
        case DOWN:
            delta = {0, DEFAULT_TEXTURE_SIZE};
            moveTexture = STRAIGHTY;
            break;
        case UP:
            delta = {0, -DEFAULT_TEXTURE_SIZE};
            moveTexture = STRAIGHTY;
            break;
        default:
            break;
    }

    return std::make_tuple(delta.first, delta.second, moveTexture);
}

bool Snake::goForwardHead()
{
    auto [dx, dy, moveTexture] = getMove();

    std::list<RenderedTexture>::iterator itH = objectState.begin();

    while(itH != objectState.end() && !isCorner(itH->type))
    {
        itH->move(dx, dy);
        itH++;
    }

    bool allDone = true;
    if(itH != objectState.end())
    {
        Position insertPos = itH->position;
        insertPos.move(dx, dy);
        objectState.insert(itH, RenderedTexture(moveTexture, insertPos.getX(), insertPos.getY()));

        allDone = false;
    }
    return allDone;
}

void Snake::goForwardTail()
{
    std::list<RenderedTexture>::iterator itT = std::prev(objectState.end());
    if( isCorner((--itT)->type) )
    {
        switch( std::next(itT)->type )
        {
            case TUP:
                (itT->type == ULRD) ? itT->changeTexture(TLEFT) : itT->changeTexture(TRIGHT);
                break;
            case TDOWN:
                (itT->type == DLRU) ? itT->changeTexture(TLEFT) : itT->changeTexture(TRIGHT);
                break;
            case TLEFT:
                (itT->type == URLD) ? itT->changeTexture(TDOWN) : itT->changeTexture(TUP);
                break;
            case TRIGHT:
                (itT->type == ULRD) ? itT->changeTexture(TDOWN) : itT->changeTexture(TUP);
                break;
            default:
                break;
        }
        objectState.pop_back();
    }
    else
    {
        itT = std::prev(objectState.end(), 2);
        itT->changeTexture((++itT)->type);
        objectState.pop_back();
    }
}


void Snake::goForward()
{
    bool straight = goForwardHead();
    if(!straight && !longer){
        goForwardTail();
    }
    else if(longer && straight){
        auto tail = std::prev(objectState.end());
        
        auto [dx, dy, MoveTexture] = getMove();

        objectState.push_back(RenderedTexture(tail->type, tail->position.getX() - dx, tail->position.getY() - dy));
        tail->changeTexture(MoveTexture);
    }
    longer = false;
}

void Snake::changeDirection()
{
    std::pair<Direction, Direction> change = {currentDir, toChange};
    Position headPos = objectState.begin()->position;

    RenderedTexture toAdd;
    TextureType textureToChange;


    if(change == std::make_pair(UP, LEFT))
    {
        textureToChange = ULRD;
        toAdd = RenderedTexture(HLEFT, headPos.getX() - DEFAULT_TEXTURE_SIZE, headPos.getY());
    }
    else if(change == std::make_pair(UP, RIGHT))
    {
        textureToChange = URLD;
        toAdd = RenderedTexture(HRIGHT, headPos.getX() + DEFAULT_TEXTURE_SIZE, headPos.getY());
    }
    else if(change == std::make_pair(DOWN, LEFT))
    {
        textureToChange = DLRU;
        toAdd = RenderedTexture(HLEFT, headPos.getX() - DEFAULT_TEXTURE_SIZE, headPos.getY());
    }
    else if(change == std::make_pair(DOWN, RIGHT))
    {
        textureToChange = DRLU;
        toAdd = RenderedTexture(HRIGHT, headPos.getX() + DEFAULT_TEXTURE_SIZE, headPos.getY());
    }
    else if(change == std::make_pair(LEFT, UP))
    {
        textureToChange = DRLU;
        toAdd = RenderedTexture(HUP, headPos.getX(), headPos.getY() - DEFAULT_TEXTURE_SIZE);
    }
    else if(change == std::make_pair(LEFT, DOWN))
    {
        textureToChange = URLD;
        toAdd = RenderedTexture(HDOWN, headPos.getX(), headPos.getY() + DEFAULT_TEXTURE_SIZE);
    }
    else if(change == std::make_pair(RIGHT, UP))
    {
        textureToChange = DLRU;
        toAdd = RenderedTexture(HUP, headPos.getX(), headPos.getY() - DEFAULT_TEXTURE_SIZE);
    }
    else if(change == std::make_pair(RIGHT, DOWN))
    {
        textureToChange = ULRD;
        toAdd = RenderedTexture(HDOWN, headPos.getX(), headPos.getY() + DEFAULT_TEXTURE_SIZE);
    }
    else
    {
        goForward();
        return;
    }
    objectState.begin()->changeTexture(textureToChange);
    objectState.push_front(toAdd);
    currentDir = toChange;
    if(!longer){
        goForwardTail();
    }
}

bool Snake::isOver()
{
    for(auto it = std::next(objectState.begin()); it != objectState.end(); it++){
        if(it->position == objectState.begin()->position)
            return true;
    }
    return false;   
}

void Snake::setChangeDir(SDL_KeyboardEvent *key)
{
    switch(key->keysym.sym)
    {
        case SDLK_RIGHT:
            toChange = RIGHT;
            break;
        case SDLK_LEFT:
            toChange = LEFT;
            break;
        case SDLK_DOWN:
            toChange = DOWN;
            break;
        case SDLK_UP:
            toChange = UP;
            break;
        default:
            break;
    }
}

void Snake::update()
{
    if(toChange != NONE){
        changeDirection();
        toChange = NONE;
    }
    else{
        goForward();
    }
    end = isOver();
    std::cout << "Score: " << score << std::endl;
}

void Snake::addScore(int s)
{
    score += s;
}

int Snake::getScore()
{
    return score;
}

void Snake::setLonger()
{
    longer = true;
}

Snake::~Snake()
{
    while(!objectState.empty())
    {
        SDL_DestroyTexture(objectState.back().texture);
        objectState.pop_back();
    }
}