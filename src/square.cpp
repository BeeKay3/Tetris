#include "square.hpp"

Square::Square(SDL_Renderer *ren, int x, int y, int w, int h) {
  renderer = ren;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
}

void Square::draw() {
  SDL_SetRenderDrawColor(renderer, 244, 130, 37, 255);
  SDL_RenderDrawRect(renderer, &r);
  SDL_RenderPresent(renderer);
}
