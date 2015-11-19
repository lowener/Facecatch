#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

void wait_for_keypressed(void);

void init_sdl(void);

SDL_Surface* load_image(char *path);

SDL_Surface* display_image(SDL_Surface *img);

void kill_image(SDL_Surface *img);

void grey(SDL_Surface *img,Uint32 *tab);

SDL_Surface* contrast_level (SDL_Surface *img);



#endif
