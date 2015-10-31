#include <stdlib.h>
#include <stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "haar_features.h"

void write (feature *feat, char *path)
{
  FILE* fichier = NULL;
  fichier = fopen(path,"w");
  if(fichier !=NULL){
fprintf(fichier,"%d ",feat->type);
  fprintf(fichier,"%d ",feat->i);
  fprintf(fichier,"%d ",feat->j);
  fprintf(fichier,"%d ",feat->w);
  fprintf(fichier,"%d ",feat->h);
  fprintf(fichier,"%d ",feat->res);
  fclose(fichier);
  }
  else
    printf("impossible d'ouvrir le fichier %s\n",path);
}

void write_vector(feature *begin,feature *end, char *path)
{
  for(size_t i =0; (i+begin) < end; i++)
    {
      write(i+begin,path);
    }
}

feature* read(char *path){
  
FILE* fichier = NULL;
  fichier = fopen(path,"r");

  if(fichier !=NULL){
    do{
      char charc= fgetc(fichier)
cars
	}while(charc != ) // a definir 



    fclose(fichier);
  }
  return NULL;

}

int main()
{
  return 0;
}
