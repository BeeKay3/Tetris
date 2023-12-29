all:
	g++ src/main.cpp src/GetTexture.cpp src/Tetromino.cpp src/board.cpp src/Menu.cpp src/Buttons.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -o tetris
	./tetris
