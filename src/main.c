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
#include "s4.h"

void write_adab(strong_classif *sc) {

  printf("void load_classif(strong_classif* sc)\n{\n");
  printf("sc->length = %i;\n", sc->length);
  for(int i = 0; i < sc->length; i++)
  {
    printf("// Weak Classifier n.%i\n", i);
    printf("sc->w[%i].coef = %lf;\n", i, sc->w[i].coef);
    printf("sc->w[%i].d->toggle = %i;\n", i, sc->w[i].d->toggle);
    printf("sc->w[%i].d->margin = %i;\n", i, sc->w[i].d->margin);
    printf("sc->w[%i].d->index = %i;\n", i, sc->w[i].d->index);
    printf("sc->w[%i].d->threshold = %lf;\n", i, sc->w[i].d->threshold);
    printf("sc->w[%i].d->error = %lf;\n", i, sc->w[i].d->error);
  }
  printf("}\n");

}

int main(/*int argc, char *argv[]*/)
{
/*
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
  */

  int pos_img = 400;
  int neg_img = 512;
  int nbimg = pos_img + neg_img;
  int* prob_weight = malloc(sizeof(int)*nbimg);
  feature** database = init_db(nbimg,pos_img,neg_img,prob_weight);

  //strong_classif *sc = adaboost(database,nbimg,250,prob_weight);
  //write_adab(sc);

  strong_classif* sc = malloc(sizeof(strong_classif));
  sc->w = malloc(250*sizeof(weak_classif));
  for(int i = 0; i < 250; i++)
  {
    sc->w[i].d = malloc(sizeof(decision));
  }
  load_classif(sc);

  int comptpos = 0;
  int comptneg = 0;
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
    {
      printf("%3d. OUI res:%f\n",j,res);
      if(j < pos_img)
        comptpos++;
    }
    else
    {
      printf("%3d. NON res.%f\n",j,res);
      if(j > pos_img)
        comptneg++;
    }
  }


  printf("--------------\n");
  printf("%i positive detected\n", (comptpos*100)/pos_img);
  printf("%i negative detected\n", (comptneg*100)/neg_img);



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
