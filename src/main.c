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

SDL_Surface* grey(char *path){
  SDL_Surface *img = load_image(path);
  Uint8 r,g,b;
  Uint32 pixel;
  int i,j;
for (i = 0; i < img->w ; i++) {

  for (j=0; j < img->h; j++) {

    pixel = getpixel(img,i,j);
    SDL_GetRGB(pixel,img->format,&r,&g,&b);
    r = g= b= 0.3*r+0.59*g+0.11*b;
    pixel= SDL_MapRGB(img->format,r,g,b);
    putpixel(img,i,j,pixel);

  }


}
return display_image(img);

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

Uint32 image_test (SDL_Surface *img,unsigned x,unsigned  y, Uint32 *tab)
{
  if(x ==0 && y ==0)
    return getpixel(img,x,y);
  if (y = 0)
    return getpixel(img,x,0) + *(tab + x-1);
  if (x = 0)
    return getpixel(img,0,y) + *(tab + (y-1)* img-> h);
  Uint32 up = *(tab + x + (y-1)*img->h);
  Uint32 left = *(tab + (x-1) + y*img->h);
  Uint32 up_left = *(tab + (x-1) + (y-1)*img->h);
  return getpixel(img,x,y)+ up + left - up_left;

  // putpixel(img,x,y,pixel);
}


Uint32* image_integrale (SDL_Surface *img)
{
  Uint32 pixel;
  size_t x,y;
  Uint32 *image = calloc(img->w*img->h, sizeof(Uint32));
  for (y = 0; y < img->h; y++)
  {
    for (x=0; x < img->w; x++)
    {
      pixel =image_test(img,w,y, image);
      *(image + x + y * img->h) = pixel;
    }
  }
    return image;
}

int main(int argc, char *argv[])
{
  printf("%d",argc);
  grey(argv[1]);
  display_image((contrast_level(load_image(argv[argc-1]))));
  display_image(image_integrale(load_image(argv[argc-1])));
  return 0;
}

