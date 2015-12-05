#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"
#include "integral_image.h"
#include "haar_features.h"
#include "training.h"
#include "sdl_functions.h"
#include "adab.h"


int main(int argc, char *argv[])
{


  if (argc == 1)
  {
    printf("where is your image?\n");
    return 1;
  }

  SDL_Surface *my_img = load_image(argv[1]);
  if (!my_img)
    return 1;
  display_image(my_img);
  //display_image((contrast_level(load_image(argv[1]))));
  Uint32* grey_array = malloc(sizeof(Uint32)*my_img->w*my_img->h);
  grey(my_img,grey_array);
  //display_image(my_img);
  //print_u32t(grey_array,my_img->w,my_img->h);
  draw_square(my_img, 40, 40, 50);
  display_image(my_img);

  printf("ADABOOST !!\n");


  int pos_img = 178;
  int neg_img = 189;
  int nbimg = pos_img + neg_img;
  int* prob_weight = malloc(sizeof(int)*nbimg);
  feature** database = init_db(nbimg,pos_img,neg_img,prob_weight);

  strong_classif *sc = adaboost(database,nbimg,40,prob_weight);
  /*
  float res = 0;
  printf("\n");
  for (int j = 0; j < nbimg; j++) {
    res = 0;
    for (int i = 0; i < sc->length; i++) {
      if (database[j][sc->w[i].d->index].res > sc->w[i].d->threshold)
        res += -sc->w[i].coef;
      else
        res +=  sc->w[i].coef;
    }
    if (res<0)
      printf("%3d. OUI res:%f\n",j,res);
    else
      printf("%3d. NON res.%f\n",j,res);
  }
  */

  printf("Strong Classifier :\n");
  for(int i = 0; i < sc->length; i++)
  {
    printf("Feat%i : error = %f, toggle = %i, threshold = %f, index = %i, coef = %f\n",i ,sc->w[i].d->error, sc->w[i].d->toggle, sc->w[i].d->threshold, sc->w[i].d->index , sc->w[i].coef);
  }

  //FREE DATABASE
  for (int i = 0; i < nbimg; i++) {
    free(database[i]);
  }
  free(database);
  return 0;
}


  /*
  if (argc == 1)
  {
    printf("where is your image?\n");
    return 1;
  }

  sdl_surface *my_img = load_image(argv[1]);
  if (!my_img)
    return 1;
  display_image(my_img);
  //display_image((contrast_level(load_image(argv[1]))));
  uint32* grey_array = malloc(sizeof(uint32)*my_img->w*my_img->h);
  grey(my_img,grey_array);
  //print_u32t(grey_array,my_img->w,my_img->h);
  Uint32* integ_array = image_integral(grey_array,my_img->w,my_img->h);
  //printf("\n---------------------------------\n");
  //print_U32t(integ_array,my_img->w,my_img->h);
  //feature *haar = compute_haar( integ_array, my_img);
  free(grey_array);
  free(integ_array);
  //free(haar);
  SDL_FreeSurface(my_img);
  */
