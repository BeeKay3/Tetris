#include<SDL2/SDL.h>

int main(int argc, char * argv[]) {
  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
  bool quit = false;
  SDL_Event e;
  while (!quit)
  {
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
