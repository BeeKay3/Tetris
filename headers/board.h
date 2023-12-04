#pragma once
#include <SDL2/SDL.h>
#include "../headers/Tetromino.h"

class Board
{
private:
    int valueGrid[20][10];
    SDL_Rect visibleGrid[20][10];
    SDL_Rect background;
    SDL_Renderer *renderer;
    SDL_Texture *baseTile;

public:
    Board(SDL_Renderer *Renderer, int BLOCKSIZE);
    ~Board();
    void update();
    void updateLog();
    bool collisionGround(SDL_Rect piece[4]);
    void insert(SDL_Rect piece[4], shape color);
};