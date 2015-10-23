#include "integral_image.h"
/*
 *typedef struct integral
 *{
 *  Uint32 *tab;
 *  int w,h;
 *}
 */



void image_test (Uint32 *tab1,size_t w, int x, int  y, Uint32 *tab2)
{
  if(x ==0 && y ==0){
    *(tab2+x+y*w) = *(tab1 + x + y*w); // getpixel(img,x,y);
    return ;
  }
  if (y == 0){
    *(tab2+ x) = *(tab1 + x) + *(tab2 + x-1);//getpixel(img,x,0) + *(tab2 + x-1);
    return ;
  }
  if (x == 0){
    *(tab2 + x + y*w) = *(tab1 + y *w)+ *(tab2 + (y-1)*w); // getpixel(img,0,y) + *(tab + (y-1)* img-> h);
    return  ;
  }
  Uint32 up = *(tab2 + x + (y-1)*w);
  Uint32 left = *(tab2 + (x-1) + y*w);
  Uint32 up_left = *(tab2 + (x-1) + (y-1)*w);
  *(tab2 + x +y*w) = *(tab1 + x + y*w)+up+left - up_left; // getpixel(img,x,y)+ up + left - up_left;

  // putpixel(img,x,y,pixel);
}


Uint32* image_integrale (Uint32 *tab,size_t w,size_t h)
{
  size_t x,y;
  Uint32 *image = calloc(w*h, sizeof(Uint32));//see manual for calloc
  for (y = 0; y < h; y++)
    {
      for (x=0; x <w; x++)
	{
	  image_test(tab,w,x,y,image);
	}
    }
  return image;
}

Uint64 integral_region(Uint64 *int_img, int img_width, int up_left_X,
                int up_left_Y, int down_right_X, int down_right_Y)
{
  Uint64 up = *(int_img + down_right_X + up_left_Y * img_width);
  Uint64 left = *(int_img + up_left_X + down_right_Y * img_width);
  Uint64 up_left = *(int_img + up_left_X + up_left_Y * img_width);
  Uint64 down_right = *(int_img + down_right_X + down_right_Y * img_width);
  return up_left + down_right - (up + left);
}
 

/* integral_image
 * Takes as parameter the image that you want to compute
 * Return a pointer to an array with the integral image
 * Use this pointer with *(ptr + x + y * Width)
 * haar features number 1
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

int haar_f2(Uint64 *int_img, SDL_Surface *img, int x, int y){
 Uint64 S1 = integral_region(int_img,img->w,x-23,y-23,x,y);
 Uint64 S2 = integral_region(int_img,img->w,x-23,y,x,y+24);
 Uint64 S3 = integral_region(int_img,img->w,x-23,y+23,x,y+2*24);
 return (S1-S2+S3);

}

int haar_f3(Uint64 *int_img,SDL_Surface *img, int x, int y){
  Uint64 S1 = integral_region(int_img,img->w,x-23,y-23,x,y);
  Uint64 S2 = integral_region(int_img,img->w,x,y-23,x+24,y);
  return S1-S2;
}

int haar_f4(Uint64 * int_img,SDL_Surface *img,int x,int y){
  Uint64 S1 = integral_region(int_img,img->w,x-23,y-23,x,y);
  Uint64 S2 = integral_region(int_img,img->w,x,y-23,x+24,y);
  Uint64 S3 = integral_region(int_img,img->w,x+24,y-23,x+2*24,y);
 return S1-S2+S3;
}

int haar_f5(Uint64 *int_img,SDL_Surface *img, int x,int y){
  Uint64 S1 = integral_region(int_img,img->w,x-23,y-23,x,y);
  Uint64 S2 = integral_region(int_img,img->w,x,y-23,x+24,y);
  Uint64 S3 = integral_region(int_img,img->w,x-23,y,x,y+24);
  Uint64 S4 = integral_region(int_img,img->w,x,y,x+24,y+24);
  return S1-S2-S3+S4;
}





