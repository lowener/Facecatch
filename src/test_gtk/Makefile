CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags gtk+-2.0`
CFLAGS= -Wall -Wextra  -std=c99 -pedantic -O3 -DNDEBUG
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image `pkg-config  --libs gtk+-2.0` -lm

SRC= 
OBJ= ${SRC:.c=.o}
 
all: main1
 
main1: ${OBJ}
 
clean:
	rm -f *~ *.o
	rm -f main1
