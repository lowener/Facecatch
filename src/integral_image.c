#include "integral_image.h"
/*
 *typedef struct integral
 *{
 *  Uint32 *tab;
 *  int w,h;
 *}
 */

Uint64 image_test (SDL_Surface *img, int x, int  y, Uint64 *tab)
{
  if(x ==0 && y ==0)
    return getpixel(img,x,y);
  if (y == 0)
    return getpixel(img,x,0) + *(tab + x-1);
  if (x == 0)
    return getpixel(img,0,y) + *(tab + (y-1)* img-> w);
  Uint64 up = *(tab + x + (y-1)*img->w);
  Uint64 left = *(tab + (x-1) + y*img->w);
  Uint64 up_left = *(tab + (x-1) + (y-1)*img->w);
  return ((Uint64)getpixel(img,x,y)+ up + left - up_left);

  // putpixel(img,x,y,pixel);
}

/* integral_image
 * Takes as parameter the image that you want to compute
 * Return a pointer to an array with the integral image
 * Use this pointer with *(ptr + x + y * Width)
 */
Uint64* image_integrale (SDL_Surface *img)
{
  int x,y;
  Uint64 *int_img=calloc(img->w*img->h,sizeof(Uint64));//see manual for calloc
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
Uint64 integral_region(Uint64 *int_img, int img_width, int up_left_X,
		int up_left_Y, int down_right_X, int down_right_Y)
{
  Uint64 up = *(int_img + down_right_X + up_left_Y * img_width);
  Uint64 left = *(int_img + up_left_X + down_right_Y * img_width);
  Uint64 up_left = *(int_img + up_left_X + up_left_Y * img_width);
  Uint64 down_right = *(int_img + down_right_X + down_right_Y * img_width);
  return up_left + down_right - (up + left);
}

/* haar features number 1
 * Check if the region of 24*24 pixels match the haar features 1
 * coordinates (x,y) correspond to down right pixel of the haar feature area
 */
int haar_f1 (Uint64 *int_img, SDL_Surface *img, int x, int y)
{
  if (x < 23 || y < 23)
    errx(1, "haar feature 1 is out of the image's dimensions");
  Uint64 integ_left = integral_region(int_img, img->w, x-23, y-23, x-12, y);
  Uint64 integ_right = integral_region(int_img, img->w, x-11, y-23, x, y);
  Uint64 threshold = (integ_left + integ_right)/2;

  if (integ_left > threshold && integ_right < threshold)
    return 1;
  else
    return 0;
}



