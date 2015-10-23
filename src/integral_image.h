#ifndef INTEGRAL_IMAGE_H_
# define INTEGRAL_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"

void image_test (Uint32 *tab1, size_t w, int  x,int y, Uint32 *tab2);
Uint32* image_integrale (Uint32 *tab,size_t w, size_t h);
int haar_f1 (Uint64 *int_img, SDL_Surface *img, int x, int y);



#endif /* !INTEGRAL_IMAGE_H_ */
