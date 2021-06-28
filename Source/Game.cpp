#include "Game.h"
#include "Snake.h"
#include "Fruit.h"

SDL_Renderer * Game::renderer = nullptr;
Game * Game::game = nullptr;
int Game::apples = 0;
int Game::bananas = 0;

Game::Game(const char * title, int x, int y, int width, int height, bool fullscreen)
{
    game = this;
    srand(time(NULL));
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0){
        std::cout << "Cannot initialize SDL subsystems" << std::endl;
        return;
    }
    std::cout << "Succesfully initialize SDL subsystems" << std::endl;

    uint32_t flags = SDL_WINDOW_SHOWN;
    if(fullscreen){
        flags |= SDL_WINDOW_FULLSCREEN;
    }

    window = SDL_CreateWindow(title, x, y, width, height, flags);
    if(window == NULL) {
        std::cout << "Cannot initialize SDL window" << std::endl;
        return;
    }
    std::cout << "Succesfully initialize SDL window" << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        std::cout << "Cannot initialize SDL renderer" << std::endl;
        return;
    }
    std::cout << "Succesfully initialize SDL renderer" << std::endl;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    bg = RenderedTexture(BACKGROUND, 0, 0);
    TextureMenager::Draw(&bg);
    SDL_RenderPresent(renderer);

    TextureMenager::font = TTF_OpenFont("../Resources/scorefont.ttf", 29);
    gameStringRect.x = GAME_SCORE_STRING_X;
    gameStringRect.y = GAME_SCORE_STRING_Y;
    gameStringRect.h = GAME_SCORE_STRING_HEIGHT;
    gameStringRect.w = GAME_SCORE_STRING_WIDTH;

    endStringRect.x = END_SCORE_STRING_X;
    endStringRect.y = END_SCORE_STRING_Y;
    endStringRect.h = END_SCORE_STRING_HEIGHT;
    endStringRect.w = END_SCORE_STRING_WIDTH;

    initBegin();
}

void Game::handle_events()
{
    input.handleEvents();
}

void Game::update()
{
    switch(actScene)
    {
        case BEGIN:
            updateBegin();
            break;
        case GAME:
            updateGame();
            break;
        case END:
            updateEnd();
            break;
        default:
            break;
    }
}

void Game::render()
{
    //Game is not running
    if(!running) return;

    SDL_RenderClear(renderer);
    TextureMenager::Draw(&bg);
    
    switch(actScene)
    {
        case BEGIN:
            renderBegin();
            break;
        case GAME:
            renderGame();
            break;
        case END:
            renderEnd();
            break;
        default:
            break;
    }
    SDL_RenderPresent(renderer);
    if(wait)
    {
        SDL_Delay(WAIT_BEFORE_PLAY);
        wait = false;
    }
}

bool Game::isRunning()
{
    return running;
}

// Clean Begin
void Game::cleanBegin()
{
    delete beginUI;
    beginUI = nullptr;
}

void Game::cleanGame()
{
    delete snake;
    snake = nullptr;
    fruits.clear();
}

void Game::cleanEnd()
{
    delete endUI;
    endUI = nullptr;
}
// Clean End


// Init Begin
void Game::initBegin()
{
    actScene = BEGIN;
    beginUI = new UIBegin();

    input.updateBegin(beginUI);
}

void Game::initGame()
{
    actScene = GAME;
    
    snake = new Snake();
    fruits.push_back(std::make_unique<Fruit>(snake, APPLE, std::vector<Position>()));

    wait = true;
    input.updateGame(snake);
}

void Game::initEnd()
{
    actScene = END;
    endUI = new UIEnd(snake->getScore());

    input.updateEnd(endUI);
}
// Init End

// Render Begin
void Game::renderBegin()
{
    beginUI->render();
}

void Game::renderGame()
{   
    snake->render();
    for(auto &fruit : fruits){
        fruit->render();
    }
    TextureMenager::DisplayScore(std::to_string(snake->getScore()), gameStringRect);
}

void Game::renderEnd()
{
    endUI->render();
    TextureMenager::DisplayEnd(std::to_string(endUI->gamescore), endStringRect);
}
// Render End

// Update Begin
void Game::updateBegin()
{
    beginUI->quitButton.update();
    if(beginUI){
        beginUI->playButton.update();
    }
}

void Game::updateGame()
{
    // Snake update
    snake->update();
    if(snake->isEnd())
    {
        initEnd();
        cleanGame();
        SDL_Delay(WAIT_BEFORE_END_MENU);
        return;
    }

    // Fruits update
    TextureType eaten = NOTHING;
    std::vector <std::list<std::unique_ptr <Fruit>>::iterator> deleteFruits;
    std::vector <Position> banned;

    for(auto it = fruits.begin(); it != fruits.end(); it++)
    {
        (*it)->update();
        if( !(*it)->isAlive() ){
            eaten = (*it)->getFruitType();
            deleteFruits.push_back(it);
        }
        else if((*it)->isEndTime()){
            deleteFruits.push_back(it);
        }
        banned.push_back((*it)->getPosition());
    }
    
    for(auto &it : deleteFruits){
        fruits.erase(it);
    }

    if(eaten == APPLE){
        fruits.push_back(std::make_unique<Fruit>(snake, APPLE, banned));
        snake->setLonger();
    }
    else{
        if(addFruit(APPLE)){
            fruits.push_back(std::make_unique<Fruit>(snake, APPLE, banned));
        }
        else if(addFruit(BANANA)){
            fruits.push_back(std::make_unique<Fruit>(snake, BANANA, banned));
        }
    }
}

void Game::updateEnd()
{
    endUI->backButton.update();
    if(endUI){
        endUI->retryButton.update();
    }
}
// Update End

bool Game::addFruit(TextureType fruit)
{
    int r = rand();
    switch(fruit)
    {
        case APPLE:
            return apples < MAX_APPLES && r % APPLE_PROB == 0;
        case BANANA:
            return bananas < MAX_BANANAS && r % BANANA_PROB == 0;
        default:
            return false;
    }
}

void Game::endGame()
{
    running = false;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(bg.texture);
    TTF_CloseFont(TextureMenager::font);
    SDL_Quit();
}