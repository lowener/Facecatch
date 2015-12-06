## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O0 -pedantic -lm -g

LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

SRC= adab.c pixel_operations.c main.c integral_image.c haar_features.c training.c sdl_functions.c save.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f main

# END
