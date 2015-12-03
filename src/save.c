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
  if (fichier!=NULL)
  {
    rewind(fichier);
    char cur;
    size_t nbspace = 0, i =0;
    int tmp =0;
    printf("%zu\n",sizeof(feature) );
    feature *tab = calloc(nbfeature,sizeof(feature));
    printf("allocation done\n");
    feature *current= malloc(sizeof(feature));
    printf("tempory allocation done\n");
    int sign=1;
    do{
      do{
        cur = fgetc(fichier);
 if (cur == ' '|| cur == '\n'){
            switch (nbspace) {
              case 0: {
                (current->type)= tmp;
//printf("add types : %i\n",tmp );
                break;
              }
              case 1: {
                (current->i) = tmp;
//printf("add i: %i\n", tmp);
                break;
              }
              case 2: {
                (current->j) = tmp;
//printf("add j: %i\n", tmp);
                break;
              }
              case 3: {
                (current->w) = tmp;
//printf("add w: %i\n", tmp);
                break;
              }
              case 4: {
                (current->h) = tmp;
//printf("add h: %i\n", tmp);
                break;
              }
              case 5:{
                (current->res) = tmp*sign;
//printf("add res: %i\n", tmp);
                break;
              }
              default:
                break;
            }
            nbspace++;
            tmp=0;
            sign =1;
 }else {
   if (cur == '-') {
     sign = -1;
   }else{
     tmp *=10;
     tmp+=(cur%48);
   }
 }
      }while(cur != '\n');
      *(tab+i)= *current;
      printf("%zu\n",i);
      i++;
    } while (i<nbfeature && cur != EOF);
    free(current);
    return tab;
  }else {
    return NULL;
  }
}
/*int main()
{
  feature*tmp=malloc(10*sizeof(feature));
  for (int i = 0; i < 10; i++) {
    feature r = {1,2,2,3,4,-100,0,0,0,0,0,0};
    *(tmp+i) = r;
  }

  write_vector(tmp,10,"test.fc");
  feature* tab = read("test.fc",10);
  for (int i = 0; i < 10; i++) {
    printf(" Haar-feat n°%d | x: %5d | y: %5d | h: %5d | w: %5d | Score: %6d |\n"
           ,(tab+i)->type,(tab+i)->i, (tab+i)->j, (tab+i)->h, (tab+i)->w, (tab+i)->res);
  }
  free(tmp);
  free(tab);
  return 0;
}*/
