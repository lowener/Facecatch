#ifndef INTEGRAL_IMAGE_H_
# define INTEGRAL_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"

Uint64 image_test (SDL_Surface *img, int x, int  y, Uint64 *tab);
Uint64* image_integrale (SDL_Surface *img);
int haar_f1 (Uint64 *int_img, SDL_Surface *img, int x, int y);



#endif /* !INTEGRAL_IMAGE_H_ */
