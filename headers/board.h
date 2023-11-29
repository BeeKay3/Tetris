#pragma once
#include <SDL2/SDL.h>

class Board
{
public:
    Board(SDL_Renderer *renderer, int BLOCKSIZE);
    ~Board();

private:
    int grid[20][10];
    SDL_Rect background;
};