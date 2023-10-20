#include "log.hpp"
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

void initialize_log(int grid[20][10]) {
  fstream init_state;

  init_state.open("./game_states/initial_state.txt", ios::in);

  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < 10; j++) {
      init_state >> grid[i][j];
      if (init_state.eof()) {break;}
    }
    if (init_state.eof()) {break;}
  }
  init_state.close();

  fstream log;
  time_t t = time(0);
  tm *now = localtime(&t);
  //year mon mday hour min
  string file_name = "./game_states/" + to_string(now->tm_year + 1900) + to_string(now->tm_mon + 1) + to_string(now->tm_mday) + to_string(now->tm_hour) + to_string(now->tm_min) + ".txt";
  log.open(file_name, ios::out);
  log << "Game played on " << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << "\n";
  log.close();
}

void update_log(int grid[20][10]) {
  return;
}
