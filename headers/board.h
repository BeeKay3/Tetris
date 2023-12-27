#pragma once
#include <SDL2/SDL.h>
#include <fstream>
#include "../headers/Tetromino.h"
#include "../headers/Menu.h"

class Board
{
private:
    int valueGrid[20][10], boardWidth, boardHeight, HORIZONTALSHIFT, VERTICALSHIFT, BLOCKSIZE, INITIAL_X, INITIAL_Y, score, totalLinesCleared, level, inum, snum;
    SDL_Rect visibleGrid[20][10], grid, bg, textBox;
    SDL_Renderer *renderer;
    SDL_Texture *baseTile, *tetrominoTile, *nextTetrominoTile, *background, *gridBackground, *textNext, *textScore, *textLevel, *textLines, *textScoreValue, *textLevelValue, *textLinesValue;
    SDL_Color textColor;
    TTF_Font *kanit;
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
