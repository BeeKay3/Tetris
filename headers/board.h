#pragma once
#include <SDL2/SDL.h>

class Board
{
private:
    int valueGrid[20][10];
    SDL_Rect visibleGrid[20][10];
    SDL_Rect background;

public:
    Board(SDL_Renderer *renderer, int BLOCKSIZE);
    ~Board();
};