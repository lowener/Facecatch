#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>


int main()
{
    //Chargement de SDL
    if (SDL_Init(SDL_INIT_VIDEO)==-1)
        errx(1,"Failed to initialized SDL: %s. \n", SDL_GetError());
    else
        printf("SDL : Initialized...");
    
    //Chemin de l'image a charger
    char *path = "./image.jpg";

    SDL_Surface *img; //Pointeur sur la structure contenant l'image
    img = IMG_Load(path);
    if (!img)    
        errx(3, "ERROR: failed to load the image");

    printf("All good...");
    return 0;
}


