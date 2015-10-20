#ifndef INTEGRAL_IMAGE_H_
# define INTEGRAL_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"

Uint32 image_test (SDL_Surface *img, int x, int  y, Uint32 *tab);
Uint32* image_integrale (SDL_Surface *img);



#endif /* !INTEGRAL_IMAGE_H_ */
