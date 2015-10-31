#include <stdlib.h>
#include <stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include "haar_features.h"

void write (feature feat,FILE* fichier)
{
 fprintf(fichier,"%d ",feat.type);
  fprintf(fichier,"%d ",feat.i);
  fprintf(fichier,"%d ",feat.j);
  fprintf(fichier,"%d ",feat.w);
  fprintf(fichier,"%d ",feat.h);
  fprintf(fichier,"%d\n",feat.res);
 
}

void write_vector(feature *begin,size_t len, char *path)
{
  FILE* fichier = NULL;
  fichier = fopen(path, "w");
if (fichier!= NULL) {
  for(size_t i =0; (i) < len; i++)
    {
      write(*(i+begin),fichier);
    }
  fclose(fichier);
}else {
  printf("impossible d'ouvrir le fichier %s\n",path );
}
}

feature* read(char *path, size_t nbfeature ){

FILE* fichier = NULL;
  fichier = fopen(path,"r");

  if(fichier!=NULL){
    rewind(fichier);
    char cur;
    char* number="";
    size_t nbspace = 0, i =0;
    int tmp=0;
    feature *tab = calloc(nbfeature,sizeof(feature)) ;
    do{

       do{
          cur = fgetc(fichier);
          if (cur == ' '){
            tmp = atoi(number);
            switch (nbspace) {
              case 0: {
                ((tab+i)->type)= tmp;
                break;
              }
              case 1: {
                ((tab+i)->i) = tmp;
                break;
              }
              case 2: {
                ((tab+i)->j) = tmp;
                break;
              }
              case 3: {
                ((tab+i)->w) = tmp;
                break;
              }
              case 4: {
                ((tab+i)->h) = tmp;
                break;
              }
              case 5:{
                ((tab+i)->res) = tmp;
                break;
              }
              default:
                break;
            }
            nbspace++;
            number =0;
          }else {
            number += cur;
          }
        }while(cur != '\n');
       i++;
    } while (i<=nbfeature && cur != EOF);
    return tab;
  }else {
    return NULL;
  }
}
