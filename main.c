#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <err.h>

SDL_Surface* display_image(SDL_Surface *img) 
{
    SDL_Surface          *screen;
    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) 
    {
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

void wait_for_keypressed(void)
{
    SDL_Event event;
    //Infinite loop, waiting for event
    for (;;)
    {
        SDL_PollEvent( &event );
        // Switch on event type
        switch (event.type)
        {
            //Someone pressed a key -> leave the function
            case SDL_KEYDOWN: return;
defaul: break;
        }
        // Loop until we got the expected event
    }
}





int main()
{
    //Chargement de SDL
    if (SDL_Init(SDL_INIT_VIDEO)==-1)
        errx(1,"Failed to initialized SDL: %s. \n", SDL_GetError());
    else
        printf("SDL : Initialized...");

    //Chemin de l'image a charger
    char *path = "./image.jpg";

    //Pointeur sur la structure contenant l'image
    SDL_Surface *img;
    img = IMG_Load(path);
    if (!img)    
        errx(3, "ERROR: failed to load the image");
    display_image(img);

    printf("All good...");
    return 0;
}


