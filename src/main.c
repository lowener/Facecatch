#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include "pixel_operations.h"
#include "integral_image.h"
#include "haar_features.h"

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }

  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }

   /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

   // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

   // wait for a key
  wait_for_keypressed();

   // return the screen for further uses
  return screen;
}

void grey(SDL_Surface *img,Uint32 *tab){
  Uint8 r,g,b;
  Uint32 pixel;
  int i,j;
  Uint32 sum;
  for (i = 0; i < img->w ; i++) {
    for (j=0; j < img->h; j++) {
      pixel = getpixel(img,i,j);
      SDL_GetRGB(pixel,img->format,&r,&g,&b);
      sum= 0.3*r+0.59*g+0.11*b;
      *(tab + i + img->w * j) = sum;
      // i = x and j = y
      // pixel= SDL_MapRGB(img->format,r,g,b);
      //putpixel(img,i,j,pixel);
    }
  }
}


SDL_Surface* contrast_level (SDL_Surface *img)
{
  Uint8 r,g,b;
  Uint32 pixel1;
  Uint32 pixel2;
  for(int i=0;i<img->w ;i++)
    {
      for(int j=0;j<img->h;j++)
	{
	  pixel1 = getpixel(img,i,j);
	  SDL_GetRGB(pixel1,img->format,&r,&g,&b);
	  pixel2 = SDL_MapRGB(img->format,255-r,255-r,255-r);
	  putpixel(img,i,j,pixel2);
	}
    }
  return img;
}

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



int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    printf("Where is your image?\n");
    return 1;
  }

  SDL_Surface *my_img = load_image(argv[1]);
  if (!my_img)
    return 1;
  display_image(my_img);
  display_image((contrast_level(load_image(argv[1]))));
  Uint32* grey_array = malloc(sizeof(Uint32)*my_img->w*my_img->h);
  grey(my_img,grey_array);
  //print_U32t(grey_array,my_img->w,my_img->h);
  Uint32* integ_array = image_integral(grey_array,my_img->w,my_img->h);
  //printf("\n---------------------------------\n");
  //print_U32t(integ_array,my_img->w,my_img->h);
  feature *haar = haar_features( integ_array, my_img, 0,1);
  free(grey_array);
  free(integ_array);
  free(haar);
  SDL_FreeSurface(my_img);
  return 0;
}


