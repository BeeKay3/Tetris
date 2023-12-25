#pragma once
#include <SDL2/SDL.h>
#include <fstream>
#include "../headers/Tetromino.h"
#include "../headers/Menu.h"

class Board
{
private:
    int valueGrid[20][10];
    SDL_Rect visibleGrid[20][10];
    SDL_Rect background;
    SDL_Renderer *renderer;
    SDL_Texture *baseTile;
    SDL_Texture *tetrominoTile;
    int boardWidth;
    int boardHeight;
    int HORIZONTALSHIFT;
    int VERTICALSHIFT;
    int BLOCKSIZE;
    int INITIAL_X;
    int INITIAL_Y;
    int score;
    int totalLinesCleared;
    int level;
    std::fstream game_state;
    Menu *menu;

public:
    Board(SDL_Renderer *Renderer, Menu *mainMenu);
    ~Board();
    menuState game();
    void update();
    void updateLog();
    bool collisionGround(SDL_Rect piece[4]);
    bool outOfLeftBounds(SDL_Rect piece[4]);
    bool outOfRightBounds(SDL_Rect piece[4]);
    bool collisionBlocks(SDL_Rect piece[4]);
    void insert(SDL_Rect piece[4], shape color, bool *dead);
    int lineClear();
};