inc = .\SDL2-2.32.10\x86_64-w64-mingw32\include
stat = .\SDL2-2.32.10\x86_64-w64-mingw32\lib

all: main.cpp
	g++ main.cpp -I$(inc) -L$(stat) -o main.exe -lmingw32 -lSDL2main -lSDL2
