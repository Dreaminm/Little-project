CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc `pkg-config --libs --cflags sdl2` -lSDL2 -lSDL2_image -lSDL2_ttf -o

all: endgame

endgame:
	$(CC) $(CFLAGS) endgame src/*.c

clean:
	rm -rf endgame

uninstall:
	rm -rf endgame

reinstall:
	make uninstall
	make
