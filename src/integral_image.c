#include "integral_image.h"
/*
 *typedef struct integral
 *{
 *  Uint32 *tab;
 *  int w,h;
 *}
*/

Uint32 image_test (SDL_Surface *img, int x, int  y, Uint32 *tab)
{
  if(x ==0 && y ==0)
    return getpixel(img,x,y);
  if (y == 0)
    return getpixel(img,x,0) + *(tab + x-1);
  if (x == 0)
    return getpixel(img,0,y) + *(tab + (y-1)* img-> w);
  Uint32 up = *(tab + x + (y-1)*img->w);
  Uint32 left = *(tab + (x-1) + y*img->w);
  Uint32 up_left = *(tab + (x-1) + (y-1)*img->w);
  return getpixel(img,x,y)+ up + left - up_left;

  // putpixel(img,x,y,pixel);
}

/* integral_image
 * Takes as parameter the image that you want to compute
 * Return a pointer to an array with the integral image
 * Use this pointer with *(ptr + x + y * Width)
 */
Uint32* image_integrale (SDL_Surface *img)
{
  int x,y;
  Uint32 *int_img=calloc(img->w*img->h,sizeof(Uint32));//see manual for calloc
  for (y = 0; y < img->h; y++)
  {
    for (x=0; x < img->w; x++)
    {
      *(int_img + x + y * img->w) = image_test(img,x,y, int_img);
    }
  }
    return int_img;
}

/* integral_region
 * Takes in parameter the integral image, it's width
 * and the position in the arrray of the up_left section (X and Y)
 * and of the down_right section.
 * Return the integral number of the region.
 */
Uint32 integral_region(Uint32 *int_img, int img_width, int up_left_X,
                       int up_left_Y, int down_right_X, int down_right_Y)
{
  Uint32 up = *(int_img + down_right_X + up_left_Y * img_width);
  Uint32 left = *(int_img + up_left_X + down_right_Y * img_width);
  Uint32 up_left = *(int_img + up_left_X + up_left_Y * img_width);
  Uint32 down_right = *(int_img + down_right_X + down_right_Y * img_width);
  return up_left + down_right - (up + left);
}
