all: fb-sim

fb-sim: main.c
	g++ main.c -o fb-sim `sdl2-config --cflags`  -lSDL2main -lSDL2 -framework Cocoa -DSSD1306_SIMULATOR

clean:
	rm fb-sim

.PHONY: all fb-sim clean