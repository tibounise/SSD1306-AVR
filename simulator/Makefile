all: simulator

simulator: main.c
	g++ main.c -o simulator `sdl2-config --cflags`  -lSDL2main -lSDL2 -framework Cocoa -D SIMULATOR

clean:
	rm simulator

.PHONY: all fb-sim clean