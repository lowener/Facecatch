## Simple SDL mini code

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-2.0`
CFLAGS= -Wall -Wextra -std=c99 -O3 -pedantic -lm -g

LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image `pkg-config --libs gtk+-2.0` -lm

SRC= adab.c pixel_operations.c integral_image.c haar_features.c training.c sdl_functions.c s4.h
#SRC=adab.c pixel_operations.c integral_image.c
OBJ= ${SRC:.c=.o}

all: main

main: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f main

# END
