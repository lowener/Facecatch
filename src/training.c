#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "haar_features.h"
#include "pixel_operations.h"
#include "training.h"
#include "sdl_functions.h"




void test_feature(feature* feat)
{
  
  char* path = "faces/face(1).bmp";
  SDL_Surface *img = load_image(path);
  display_image(img);
  printf("type = %i\n", feat->type);
}
