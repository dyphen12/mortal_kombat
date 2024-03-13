all:
	g++ -Isrc/include -Lsrc/lib -o main main.cpp src/include/match.cpp src/include/karateka.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
