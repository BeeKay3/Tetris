#ifndef SQUARE_H_
#define SQUARE_H_
#include<SDL2/SDL.h>

class Square {
  private:
    SDL_Rect r;
    SDL_Renderer *renderer;
  public:
    Square(SDL_Renderer *ren, int x, int y, int w, int h);
    void draw();
};

#endif // SQUARE_H_
