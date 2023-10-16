#include <SDL2/SDL.h>
#include <fstream>
#include <ctime>
#include <string>
// #include "src/square.hpp"

using namespace std;

void initial_state(int grid[20][10]) {
  fstream init_state;

  init_state.open("./game_states/initial_state.txt", ios::in);

  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < 10; j++) {
      init_state >> grid[i][j];
      if(init_state.eof()){break;}
    }
    if(init_state.eof()){break;}
  }
  init_state.close();

  fstream log;
  time_t t = time(0);
  tm *now = localtime(&t);
  //year mon mday hour min
  string file_name = "./game_states/" + to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1) + to_string(now->tm_mday) + to_string(now->tm_hour) + to_string(now->tm_min) + ".txt";
  log.open(file_name, ios::out);
  log.close();
}

void bg(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}

void square(SDL_Renderer *renderer, SDL_Rect r){
  SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 244 ,130, 37, 255);
  SDL_RenderFillRect(renderer, &r);
  SDL_RenderPresent(renderer);
}

void quitSDL(SDL_Window *win, SDL_Renderer *ren){
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
}

#define initial_x 300
#define initial_y 0

int main(int argc, char * argv[]) {
  int grid[20][10];

  initial_state(grid);

  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  bool run = true;
  SDL_Event e;
  SDL_Rect r = {initial_x, initial_y, 80, 80};

  // Square s(renderer, initial_x, initial_y, 30, 30);
  // s.draw();

  while (run) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        run = false;
      }
    }
    if (r.y < 640) {
      square(renderer, r);
      r.y += 80;
    }
    SDL_Delay(100);
  }

  quitSDL(window, renderer);
  return EXIT_SUCCESS;
}
