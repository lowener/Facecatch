#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "haar_features.h"
#include "integral_image.h"
#include "pixel_operations.h"
#include "training.h"
#include "sdl_functions.h"




/*

int test_feature(feature* feat)
{
  int i = 1;
  char* path = "faces/face(";

  SDL_Surface *img = load_image(path);
  //display_image(img);
  printf("type = %i\n", feat->type);
  Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
  grey(img, grey_img);
  Uint32* int_img = image_integral(grey_img, img->w, img->h);

  int haar_value = 0;

  switch(feat->type)
  {
    case 1:
      haar_value = haar_f1(int_img, feat->w, ;
      break;

    case 2:
      haar_value = haar_f2(int_img, feat->w, ;
      break;

    case 3:
      haar_value = haar_f3(int_img, feat->w, ;
      break;

    case 4:
      haar_value = haar_f4(int_img, feat->w, ;
      break;

    default :
      haar_value = haar_f5(int_img, feat->w, ;
      break;
  }

  free(grey_img);
  free(int_img);
  return haar_value;
}
*/


feature* compute_variance(feature** db, int nbimg)
{
  feature *result = calloc(162336,sizeof(feature));
  for (int i = 0; i < 162336; i++) {
    int mean = 0;
    feature current = db[1][i];
    for (int j = 0; j < nbimg; j++) {
      mean +=  db[j][i].res;
    }
    mean = mean / nbimg;
    int total = 0;
    for (int j = 0; j < nbimg; j++) {
      db[j][i].res =(db[j][i].res-mean)*(db[j][i].res-mean)/nbimg;
      total += db[j][i].res;
    }
    total = total / nbimg;
    current.res = total;
    *(result + i) = current;
  }
  return result;
}
