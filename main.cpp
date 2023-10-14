#include<SDL2/SDL.h>
#include<fstream>
#include<ctime>
#include<string>

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
}

void create_log_file(){
  fstream log;
  time_t t = time(0);
  tm *now = localtime(&t);
  //year mon mday hour min
  string file_name = "./game_states/" + to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1) + to_string(now->tm_mday) + to_string(now->tm_hour) + to_string(now->tm_min) + ".txt";
  log.open(file_name, ios::out);
  log.close();
}

int main(int argc, char * argv[]) {
  int grid[20][10];

  initial_state(grid);
  create_log_file();

  SDL_Window *window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800, SDL_WINDOW_SHOWN);
  bool run = true;
  SDL_Event e;
  while (run) {
    if (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        run = false;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
