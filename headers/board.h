#pragma once
#include <SDL2/SDL.h>

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
};