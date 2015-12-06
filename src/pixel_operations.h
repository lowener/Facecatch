// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);


void Stretch_Nearest(SDL_Surface* src, SDL_Surface* dest);

SDL_Surface *Stretchblit(SDL_Surface* src);

# endif
