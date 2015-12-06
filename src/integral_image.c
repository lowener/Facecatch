#include "integral_image.h"


void compute_integral (Uint32 *tab1,size_t w, int x, int  y, Uint32 *tab2)
{
  if(x ==0 && y ==0){
    *(tab2+x+y*w) = *(tab1 + x + y*w); // getpixel(img,x,y);
    return ;
  }
  if (y == 0){
    *(tab2+ x) = *(tab1 + x) + *(tab2 + x-1);
//getpixel(img,x,0) + *(tab2 + x-1);
    return ;
  }
  if (x == 0){
    *(tab2 + x + y*w) = *(tab1 + y *w)+ *(tab2 + (y-1)*w);
 // getpixel(img,0,y) + *(tab + (y-1)* img-> h);
    return  ;
  }
  Uint32 up = *(tab2 + x + (y-1)*w);
  Uint32 left = *(tab2 + (x-1) + y*w);
  Uint32 up_left = *(tab2 + (x-1) + (y-1)*w);
  *(tab2 + x +y*w) = *(tab1 + x + y*w)+up+left - up_left;
  // getpixel(img,x,y)+ up + left - up_left;

  // putpixel(img,x,y,pixel);
}


/* integral_image
 * Takes as parameter the image that you want to compute
 * Return a pointer to an array with the integral image
 * Use this pointer with *(ptr + x + y * Width)
 */

Uint32* image_integral (Uint32 *tab,size_t w,size_t h)
{
  size_t x,y;
  Uint32 *image = calloc(w*h, sizeof(Uint32));//see manual for calloc
  for (y = 0; y < h; y++)
    {
      for (x=0; x <w; x++)
	{
	  compute_integral(tab,w,x,y,image);
	}
    }
  return image;
}

Uint32 integral_region(Uint32 *int_img, size_t img_width, int up_left_X,
                int up_left_Y, int down_right_X, int down_right_Y)
{
  down_right_X--;
  down_right_Y--;
  up_left_X--;
  up_left_Y--;
  Uint32 up = *(int_img + down_right_X + up_left_Y * img_width);
  Uint32 left = *(int_img + up_left_X + down_right_Y * img_width);
  Uint32 up_left = *(int_img + up_left_X + up_left_Y * img_width);
  Uint32 down_right = *(int_img + down_right_X + down_right_Y * img_width);
  return up_left + down_right - (up + left);
}

