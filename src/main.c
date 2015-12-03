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


/* This function test if the integral image overflow at some point
 *  on the Uint64 type
 */
int test_overflow(Uint64 *integ, SDL_Surface *img)
{
  int overflow = 0;
  int i = 1;
  Uint64 prev = 0;
  printf("### TEST OVERFLOW : ###\n");
  while (i < img->w && !overflow)
  {
    Uint64 x = *(integ + i + (img->h - 1) * img->w);
    printf("i = %i, val = %lu\n", i, x);
    if (x < prev)
      overflow = 1;
    prev = x;
    i++;
  }
  if (overflow)
    printf("OVERFLOW !\n");
  return overflow;
}




void print_U32t(Uint32 *tab,size_t w,size_t h){
  size_t x,y;
  for (y = 0; y < h; y++){
    for (x=0; x <w; x++)
      printf(" %6u ",tab[x+y*w]);
    printf("\n");
  }
}



int main(/*int argc, char *argv[]*/)
{

  feature** database = init_db(178);

  for (int i = 480; i < 500; i++) {
    feature *f = &database[42][i];
    printf("Haar-feat n°%d | x: %5d | y: %5d | h: %5d | w: %5d | res: %6d | criteria: %6d | threshold: %f | \n",i,f->i, f->j, f->h, f->w,f->res, f->criteria, f->threshold);
  }


  classifier* k = get_important_feats(database, 178);

  for (int i = 0; i < 10; i++) {
    feature *f = &(k->feats[42+i]);
    printf(" Haar-feat n°%d | x: %5d | y: %5d | h: %5d | w: %5d | Score: %6d |\n"
           ,i,f->i, f->j, f->h, f->w, f->res);
  }

  classifier* new_k = generate_new_classifier(database, k, 300, 178);

  printf("%i elements in classifier\n", new_k->length);


  for (int i = 0; i < 10; i++) {
    feature *f = &(new_k->feats[42+i]);
    printf(" Strong classifier n°%d | x: %5d | y: %5d | h: %5d | w: %5d | Score: %6d |\n"
           ,i, f->i, f->j, f->h, f->w, f->res);
  }

  for (int i =0 ; i < 178; i++) {
    free(database[i]);
  }

  free(new_k->feats);
  free(new_k);
  free(k->feats);
  free(k);
  free(database);
  return 0;
}


  /*
  if (argc == 1)
  {
    printf("Where is your image?\n");
    return 1;
  }

  SDL_Surface *my_img = load_image(argv[1]);
  if (!my_img)
    return 1;
  display_image(my_img);
  //display_image((contrast_level(load_image(argv[1]))));
  Uint32* grey_array = malloc(sizeof(Uint32)*my_img->w*my_img->h);
  grey(my_img,grey_array);
  //print_U32t(grey_array,my_img->w,my_img->h);
  Uint32* integ_array = image_integral(grey_array,my_img->w,my_img->h);
  //printf("\n---------------------------------\n");
  //print_U32t(integ_array,my_img->w,my_img->h);
  //feature *haar = compute_haar( integ_array, my_img);
  free(grey_array);
  free(integ_array);
  //free(haar);
  SDL_FreeSurface(my_img);
  */
