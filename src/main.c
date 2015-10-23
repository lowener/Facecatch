#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>
# include "pixel_operations.h"

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

void print_U32t(Uint32 *tab,size_t w,size_t h){
  size_t x,y;
  for (y = 0; y < h; y++){
    for (x=0; x <w; x++)
      printf(" %6u ",tab[x+y*w]);
    printf("\n");
  }
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




int main(int argc, char *argv[])
{ 
  SDL_Surface *my_img = load_image(argv[1]);
  display_image(my_img);
  Uint32* powney = malloc(sizeof(Uint32)*my_img->w*my_img->h);
  grey(my_img,powney);
  print_U32t(powney,my_img->w,my_img->h);
  Uint32* poney = image_integrale(powney,my_img->w,my_img->h);
  printf("\n---------------------------------\n");
  print_U32t(poney,my_img->w,my_img->h);
  return argc;
}


