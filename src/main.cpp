#include <SDL2/SDL.h>

using namespace std;

int SCREENWIDTH = 1920, SCREENHEIGHT = 1080;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *argv[])
{
  window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bool run = true;
  SDL_Event e;

  while (run)
  {
    if (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        run = false;
      }
    }
  }
  return 0;
}
