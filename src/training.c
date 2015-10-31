#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "haar_features.h"
#include "integral_image.h"
#include "pixel_operations.h"
#include "training.h"
#include "sdl_functions.h"


feature** init_db(int nb_img)
{
  feature** database = malloc(nb_img*162336*sizeof(feature));
  printf("Database allocated...\n");
  printf("Filling database\n");
  
  for(int i = 1; i <= nb_img; i++)
  {
    char path[20];
    strcpy(path, "faces/face(");
    char str[5];  
    sprintf(str,"%i", i);  
    strcat(path, str);
    strcat(path, ").bmp");
    puts(path);

    SDL_Surface *img = load_image(path);
    display_image(img);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);
    
    *(database + i - 1) = haar_features(int_img, img, 0, 0);

    free(grey_img);
    free(int_img);
  }


  printf("n1, w = %i ; h = %i ; res = %i\n", database[0]->w, database[0]->h, database[0]->res);
  printf("n2, w = %i ; h = %i ; res = %i\n", database[0][250].w, database[0][250].h, database[0][250].res);
  return database;
}



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
