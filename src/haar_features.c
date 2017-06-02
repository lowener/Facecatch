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
  static int index = 0;
  static int nbi = 0;
  feat->type = type;
  feat->i = j; // Everything is under control
  feat->j = i;
  feat->w = w;
  feat->h = h;
  feat->res = res;
  feat->index = index;
  feat->nbimg = nbi;
  index = (index + 1)%162336;
  if (!index)
    nbi++;
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


/* haar_features
 * Parameters: feature array, integral image, image, position x and y
 * of the 24x24 area
 * It's calling fonction is compute_haar
 * Compute the Haar features in the area of 24x24
 * Result: array of features
 */

feature* haar_features(Uint32 *int_img, int w, int x, int y)
{
  feature *array_feat = calloc(162336, sizeof(feature));
  feature *current = malloc(sizeof(feature));
  int index_array = 0;
  index_array = haar_f1(int_img,w,array_feat,current,index_array,x,y);
  index_array = haar_f2(int_img,w,array_feat,current,index_array,x,y);
  index_array = haar_f3(int_img,w,array_feat,current,index_array,x,y);
  index_array = haar_f4(int_img,w,array_feat,current,index_array,x,y);
  index_array = haar_f5(int_img,w,array_feat,current,index_array,x,y);
  free(current);
  return array_feat;
}

void f1(Uint32 *int_img, size_t width, feature *array_feat,
        feature *current, int index_array, int x, int y,
        int i, int j, int h, int w)
{
  Uint32 S1 = integral_region(int_img, width,
                              x+i, y+j,   x+i+h-1, y+j+w-1);
  Uint32 S2 = integral_region(int_img, width,
                              x+i, y+j+w, x+i+h-1, y+j+w*2-1);
  build_feat(current,1,i,j,w,h,S1-S2);
  *(array_feat + index_array) = *current;
}

void f2(Uint32 *int_img, size_t width, feature *array_feat,
        feature *current, int index_array, int x, int y,
        int i, int j, int h, int w)
{
  Uint32 S1 = integral_region(int_img, width,
                              x+i, y+j,   x+i+h-1, y+j+w-1);
  Uint32 S2 = integral_region(int_img, width,
                              x+i, y+j+w, x+i+h-1, y+j+w*2-1);
  Uint32 S3 = integral_region(int_img, width,
                              x+i, y+j+w*2, x+i+h-1, y+j+w*3-1);
  build_feat(current,2,i,j,w,h,S1-S2+S3);
  *(array_feat + index_array) = *current;

}

void f3(Uint32 *int_img, size_t width, feature *array_feat,
        feature *current, int index_array, int x, int y,
        int i, int j, int h, int w)
{
  Uint32 S1 = integral_region(int_img, width,
                              x+i, y+j,   x+i+h-1, y+j+w-1);
  Uint32 S2 = integral_region(int_img, width,
                              x+i+h, y+j, x+i+2*h-1, y+j+w-1);
  build_feat(current,3,i,j,w,h,S1-S2);
  *(array_feat + index_array) = *current;

}
void f4(Uint32 *int_img, size_t width, feature *array_feat,
        feature *current, int index_array, int x, int y,
        int i, int j, int h, int w)
{
  Uint32 S1 = integral_region(int_img, width,
                              x+i,     y+j, x+i+h-1,   y+j+w-1);
  Uint32 S2 = integral_region(int_img, width,
                              x+i+h,   y+j, x+i+2*h-1, y+j+w-1);
  Uint32 S3 = integral_region(int_img, width,
                              x+i+2*h, y+j, x+i+3*h-1, y+j+w-1);
  build_feat(current,4,i,j,w,h,S1-S2+S3);
  *(array_feat + index_array) = *current;

}

void f5(Uint32 *int_img, size_t width, feature *array_feat,
        feature *current, int index_array, int x, int y,
        int i, int j, int h, int w)
{
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

}

feature* classif_features(Uint32 *int_img, int w, int x, int y, strong_classif*sc)
{
  feature *array_feat = calloc(250, sizeof(feature));
  feature *current = malloc(sizeof(feature));
  for(int a = 0; a < 250 ; a++)
  {
    if (sc->w[a].d->type == 1)
      f1(int_img,w,array_feat,current,a,x,y,sc->w[a].d->i,
         sc->w[a].d->j, sc->w[a].d->h, sc->w[a].d->w);
    else if (sc->w[a].d->type == 2)
      f2(int_img,w,array_feat,current,a,x,y,sc->w[a].d->i,
         sc->w[a].d->j, sc->w[a].d->h, sc->w[a].d->w);
    else if (sc->w[a].d->type == 3)
      f3(int_img,w,array_feat,current,a,x,y,sc->w[a].d->i,
         sc->w[a].d->j, sc->w[a].d->h, sc->w[a].d->w);
    else if (sc->w[a].d->type == 4)
      f4(int_img,w,array_feat,current,a,x,y,sc->w[a].d->i,
         sc->w[a].d->j, sc->w[a].d->h, sc->w[a].d->w);
    else if (sc->w[a].d->type == 5)
      f5(int_img,w,array_feat,current,a,x,y,sc->w[a].d->i,
         sc->w[a].d->j, sc->w[a].d->h, sc->w[a].d->w);
  }
  free(current);
  return array_feat;
}
