#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include"adab.h"

typedef struct selection
{
  float res;
  int x;
  int y;
  int e;
}selection;

void wait_for_keypressed(void);

void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

void grey(SDL_Surface *img,Uint32 *tab);

SDL_Surface* contrast_level (SDL_Surface *img);

void draw_square(SDL_Surface *img, int x, int y, int width);

void detect_faces(SDL_Surface *img, SDL_Surface* clone, strong_classif* sc, int x, int y, int e);

void analyse_image(SDL_Surface* img, SDL_Surface* clone);

void facial_recognition(char* path);

#endif
