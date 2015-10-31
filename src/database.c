#include <stdlib.h>
#include <stdio.h>
#include "database.h"


void write(feature feats, size_t size, char* fichier)
{   
  FILE *fichier;
  fichier = fopen(fichier, "wb+");
  fwrite(feats, size, 1, fichier);
  fclose(fichier);
}

void read(feature feats, size_t size, char* fichier) 
{
  fichier = fopen(fichier, "rb");
  fread(feats, size, 1, fichier);
}


