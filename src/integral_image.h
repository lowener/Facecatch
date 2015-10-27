#ifndef INTEGRAL_IMAGE_H_
# define INTEGRAL_IMAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"

void compute_integral (Uint32 *tab1, size_t w, int  x,int y, Uint32 *tab2);
Uint32* image_integral (Uint32 *tab,size_t w, size_t h);
Uint32 integral_region(Uint32 *int_img, size_t img_width, int up_left_X,
                       int up_left_Y, int down_right_X, int down_right_Y);


#endif /* !INTEGRAL_IMAGE_H_ */
