#include<iostream>
#include<fstream>

using namespace std;

int main() {
  fstream init_state;

  init_state.open("./game_states/initial_state.txt", ios::in);

  if (!init_state) {
    cout << "file no\n";
  } else {
    cout << "file yes\n";
  }

  int grid[20][10], i, j;
  for(i = 0; i < 20; i++) {
    for(j = 0; j< 10; j++) {
      init_state >> grid[i][j];
      if(init_state.eof()){
        break;
      }
    }
    if(init_state.eof()){
      break;
    }
  }

  for (i = 0; i < 20; i++) {
    for (j = 0; j < 10; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  init_state.close();
  return 0;
}
