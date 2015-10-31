#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "integral_image.h"
#include "haar_features.h"

 /* haar features
  * Check if the region of 24*24 pixels match the haar features 1
  * coordinates (x,y) correspond to down right pixel of the haar feature area
  */



void build_feat(feature *feat, int type, int i, int j, int w, int h, int res)
{
//  printf("build\n");
  feat->type = type;
  feat->i = i;
  feat->j = j;
  feat->w = w;
  feat->h = h;
  feat->res = res;
//  printf("build OK\n");
}

/* compute_haar
 * Parameters: integral image, image
 * Compute the Haar features in the whole image by calling haar_features
 * Result: Array of array of Haar features
 */

feature* compute_haar(Uint32 *int_img, SDL_Surface *img)
{
  feature *array_feat = calloc(img->w * img-> h, sizeof(feature));
 int size = 0;
 for (int y = 0; y < img->h; y++) {
   for (int x = 0; x < img->w; x++) {
     *(array_feat + size) = *haar_features(int_img, img, x,y);
     size++;
     printf("%d/%d\n",size,img->w*img->h);
   }
 }
 
 return array_feat;
}


/* haar_features
 * Parameters: feature array, integral image, image, position x and y of the 24x24 area
 * It's calling fonction is compute_haar
 * Compute the Haar features in the area of 24x24
 * Result: array of features
 */

feature* haar_features(Uint32 *int_img, SDL_Surface *img, int x, int y)
{
  feature *array_feat = calloc(162400, sizeof(feature));
  feature *current = malloc(sizeof(feature));
  int index_array = 0;
  //printf("ok ...\n");
  index_array = haar_f1(int_img,img->w,array_feat,current,index_array,x,y);
  //printf("Haar 1: %d features\n",index_array);
  index_array = haar_f2(int_img,img->w,array_feat,current,index_array,x,y);
  //printf("Haar 2: %d features\n",index_array);
  index_array = haar_f3(int_img,img->w,array_feat,current,index_array,x,y);
  //printf("Haar 3: %d features\n",index_array);
  index_array = haar_f4(int_img,img->w,array_feat,current,index_array,x,y);
  //printf("Haar 4: %d features\n",index_array);
  index_array = haar_f5(int_img,img->w,array_feat,current,index_array,x,y);
  //printf("Haar 5: %d features\n",index_array);
  free(current);
  return array_feat;
}


int haar_f1 (Uint32 *int_img, size_t width, feature *array_feat,
             feature *current, int index_array, int x, int y)
{
  int i,j,h,w;
  for (i=1; i <= 24; i++) {
    for (j=1; j <= 24; j++) {
      for (h=1; i+h-1<=24; h++) {
        for (w=1; j+2*w-1<=24; w++) {
          Uint32 S1 = integral_region(int_img, width,
                                      x+i, y+j,   x+i+h-1, y+j+w-1);
          Uint32 S2 = integral_region(int_img, width,
                                      x+i, y+j+w, x+i+h-1, y+j+w*2-1);
          build_feat(current,1,i,j,w,h,S1-S2);
          *(array_feat + index_array) = *current;
          (index_array)++;
        }
      }
    }
  }
  return index_array;
}


int haar_f2 (Uint32 *int_img, size_t width, feature *array_feat,
             feature *current, int index_array, int x, int y)
{
  int i,j,h,w;
  for (i=1; i <= 24; i++) {
    for (j=1; j <= 24; j++) {
      for (h=1; i+h-1<=24; h++) {
        for (w=1; j+3*w-1<=24; w++) {
          Uint32 S1 = integral_region(int_img, width,
                                      x+i, y+j,   x+i+h-1, y+j+w-1);
          Uint32 S2 = integral_region(int_img, width,
                                      x+i, y+j+w, x+i+h-1, y+j+w*2-1);
          Uint32 S3 = integral_region(int_img, width,
                                      x+i, y+j+w*2, x+i+h-1, y+j+w*3-1);
          build_feat(current,2,i,j,w,h,S1-S2+S3);
          *(array_feat + index_array) = *current;
          (index_array)++;
        }
      }
    }
  }
  return index_array;
}


int haar_f3 (Uint32 *int_img, size_t width, feature *array_feat,
             feature *current, int index_array, int x, int y)
{
  int i,j,h,w;
  for (i=1; i <= 24; i++) {
    for (j=1; j <= 24; j++) {
      for (h=1; i+2*h-1<=24; h++) {
        for (w=1; j+w-1<=24; w++) {
          Uint32 S1 = integral_region(int_img, width,
                                      x+i, y+j,   x+i+h-1, y+j+w-1);
          Uint32 S2 = integral_region(int_img, width,
                                      x+i+h, y+j, x+i+2*h-1, y+j+w-1);
          build_feat(current,3,i,j,w,h,S1-S2);
          *(array_feat + index_array) = *current;
          (index_array)++;
        }
      }
    }
  }
  return index_array;
}


int haar_f4 (Uint32 *int_img, size_t width, feature *array_feat,
             feature *current, int index_array, int x, int y)
{
  int i,j,h,w;
  for (i=1; i <= 24; i++) {
    for (j=1; j <= 24; j++) {
      for (h=1; i+3*h-1<=24; h++) {
        for (w=1; j+w-1<=24; w++) {
          Uint32 S1 = integral_region(int_img, width,
                                      x+i,     y+j, x+i+h-1,   y+j+w-1);
          Uint32 S2 = integral_region(int_img, width,
                                      x+i+h,   y+j, x+i+2*h-1, y+j+w-1);
          Uint32 S3 = integral_region(int_img, width,
                                      x+i+2*h, y+j, x+i+3*h-1, y+j+w-1);
          build_feat(current,4,i,j,w,h,S1-S2+S3);
          *(array_feat + index_array) = *current;
          (index_array)++;
        }
      }
    }
  }
  return index_array;
}


int haar_f5 (Uint32 *int_img, size_t width, feature *array_feat,
             feature *current, int index_array, int x, int y)
{
  int i,j,h,w;
  for (i=1; i <= 24; i++) {
    for (j=1; j <= 24; j++) {
      for (h=1; i+2*h-1<=24; h++) {
        for (w=1;j+2*w-1<=24; w++) {
          Uint32 S1 = integral_region(int_img, width,
                                      x+i,     y+j,   x+i+h-1,   y+j+w-1);
          Uint32 S2 = integral_region(int_img, width,
                                      x+i+h,   y+j,   x+i+2*h-1, y+j+w-1);
          Uint32 S3 = integral_region(int_img, width,
                                      x+i,     y+j,   x+i+h-1,   y+j+2*w-1);
          Uint32 S4 = integral_region(int_img, width,
                                      x+i+h,   y+j+w, x+i+2*h-1, y+j+2*w-1);
          build_feat(current,5,i,j,w,h,S1-S2-S3+S4);
          *(array_feat + index_array) = *current;
          (index_array)++;
        }
      }
    }
  }
  return index_array;
}
/*
int near(float x)
{
  int a = floor(x);
  if (a - x > 0.5)
    a++;
  return a;
}
*/
/* scaling
 *Input: intregral image, e*e image (e>=24), Haar like feature
 *Compute a feature scaled to the image
 *Output: A Haar-like feature with all the good values
 */
/*
void scaling(Uint32 *int_img, SDL_Surface *img, feature *arr)
{
  int e = img->w;

  if (arr -> type == 1)
  {
    arr->type = 2*arr->w*arr->h;
    arr->i = near(arr->i * e / 24);
    arr->j = near(arr->j * e / 24);
    arr->h = near(arr->h * e / 24);
    int k = 0;
    while (k <= near(1+2*arr->w*e/24) && 2*k <= e-arr->j+1)
      k++;
    arr->w = k;
    Uint32 S1 = integral_region(int_img, e, arr->i,arr->j,
                                arr->i+arr->h-1,arr->w-1);
    Uint32 S2 = integral_region(int_img, e, arr->i, arr->j+arr->w,
                                arr->i+arr->h-1,arr->j+arr->w*2-1);
    arr->res = (S1 - S2)*arr->type / (2*arr->w*arr->h);
  }
  else if (arr -> type == 2)
  {
    arr->type = 3*arr->w*arr->h;
    arr->i = near(arr->i * e / 24);
    arr->j = near(arr->j * e / 24);
    arr->h = near(arr->h * e / 24);
    int k = 0;
    while (k <= near(1+3*arr->w*e/24) && 3*k <= e-arr->j+1)
      k++;
    arr->w = k;
    Uint32 S1 = integral_region(int_img, e, arr->i,arr->j,
                                arr->i+arr->h-1,arr->w-1);
    Uint32 S2 = integral_region(int_img, e, arr->i, arr->j+arr->w,
                                arr->i+arr->h-1,arr->j+arr->w*2-1);
    Uint32 S3 = integral_region(int_img, e, arr->i,arr->j+2*arr->w,
                                arr->i+arr->h-1,arr->j+arr->w*3-1);
    arr->res = (S1 - S2 + S3)*arr->type / (3*arr->w*arr->h);
  }
  else if (arr -> type == 3)
  {
    arr->type = 2*arr->w*arr->h;
    arr->i = near(arr->i * e / 24);
    arr->j = near(arr->j * e / 24);
    arr->w = near(arr->w * e / 24);
    int k = 0;
    while (k <= near(1+2*arr->h*e/24) && 2*k <= e-arr->i+1)
      k++;
    arr->h = k;
    Uint32 S1 = integral_region(int_img, e, arr->i,arr->j,
                                arr->i+arr->h-1,arr->j + arr->w-1);
    Uint32 S2 = integral_region(int_img, e, arr->i+arr->h, arr->j,
                                arr->i+arr->h*2-1,arr->j+arr->w-1);
    arr->res = (S1 - S2)*arr->type / (2*arr->w*arr->h);
  }
  else if (arr -> type == 4)
  {
    arr->type = 3*arr->w*arr->h;
    arr->i = near(arr->i * e / 24);
    arr->j = near(arr->j * e / 24);
    arr->w = near(arr->w * e / 24);
    int k = 0;
    while (k <= near(1+3*arr->h*e/24) && 3*k <= e-arr->i-1)
      k++;
    arr->h = k;
    Uint32 S1 = integral_region(int_img, e, arr->i,arr->j,
                                arr->i+arr->h-1,arr->j+arr->w-1);
    Uint32 S2 = integral_region(int_img, e, arr->i+arr->h,arr->j,
                                arr->i+2*arr->h-1,arr->j+arr->w-1);
    Uint32 S3 = integral_region(int_img, e, arr->i+arr->h*2,arr->j,
                                arr->i+3*arr->h-1,arr->j+arr->w-1);
    arr->res = (S1 - S2 + S3)*arr->type / (3*arr->w*arr->h);
  }
  else if (arr -> type == 5)
  {
    arr->type = 4*arr->w*arr->h;
    arr->i = near(arr->i * e / 24);
    arr->j = near(arr->j * e / 24);
    int k = 0;
    while (k <= near(1+2*arr->w*e/24) && 2*k <= e-arr->j+1)
      k++;
    arr->w = k;
    k = 0;
    while (k <= near(1+2*arr->h*e/24) && 2*k <= e-arr->j+1)
      k++;
    arr->h = k;
    Uint32 S1 = integral_region(int_img, e, arr->i,arr->j,
                                arr->i+arr->h-1,arr->w-1+arr->j);

    Uint32 S2 = integral_region(int_img, e, arr->i+arr->h,arr->j,
                                arr->i+arr->h*2-1,arr->w-1+arr->j);

    Uint32 S3 = integral_region(int_img, e, arr->i,arr->j + arr->w,
                                arr->i+arr->h-1,arr->w*2-1+arr->j);

    Uint32 S4 = integral_region(int_img, e, arr->i+arr->h,arr->j+arr->w,
                                arr->i+arr->h*2-1,arr->w*2-1+arr->j);
    arr->res = (S1 - S2-S3+S4)*arr->type / (4*arr->w*arr->h);
  }
}
*/
