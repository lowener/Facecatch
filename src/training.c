#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "haar_features.h"
#include "integral_image.h"
#include "pixel_operations.h"
#include "training.h"
#include "sdl_functions.h"


feature** init_db(int nb_img)
{
  feature** database = malloc(nb_img*162336*sizeof(feature));
  printf("Database allocated...\n");
  printf("Filling database\n");
  
  for(int i = 1; i <= nb_img; i++)
  {
    char path[20];
    strcpy(path, "faces/face(");
    char str[5];  
    sprintf(str,"%i", i);  
    strcat(path, str);
    strcat(path, ").bmp");
    puts(path);

    SDL_Surface *img = load_image(path);
    //display_image(img);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);
    
    *(database + i - 1) = haar_features(int_img, img, 0, 0);

    free(grey_img);
    free(int_img);
  }


  printf("n1, w = %i ; h = %i ; res = %i\n", database[10][250].w, database[10][250].h, database[10][250].res);
  printf("n2, w = %i ; h = %i ; res = %i\n", database[0][250].w, database[0][250].h, database[0][250].res);
  return database;
}





/* harmonize
 * As parameters: Vector of the weight of the image,
 *                vector of the modification(0/1), nb img
 * Harmonize the weight of the image
 * Return the new Vector of weight
 */
float *harmonize(float weight_vect[], int modif_array[], int nbimg)
{
  int index = 0;
  int nbmodif = 0;
  float pas = 5/nbimg;
  for (index = 0; index < nbimg; index++) {
    if (modif_array[index] == 1) {
      weight_vect[index] += pas;
      nbmodif++;
    }
  }
  float sum = 1 + pas * nbmodif;
  float new_total_weight = 1/sum;
  for (index = 0; index < nbimg && nbmodif; index++) {
    weight_vect[index] = weight_vect[index] * new_total_weight;
    nbmodif--;
  }
    return weight_vect;
}



classifier* get_important_feats(feature** database, int nb_img)
{
  feature* feats = malloc(162336*sizeof(feature));
  feats = database[0];
  //initialize nb_match at values 0
  for(int i = 0; i < 162336; i++)
  {
    feats[i].nb_match = 0;   
  }
    
  //calculating nb_match
  for(int i = 0; i < 162336; i++)
  {
    for(int j = 0; j < nb_img; j++)
    { 
      if(database[j][i].res > 0 && database[j][i].w != 1 && 
      database[j][i].h != 1)
        feats[i].nb_match++;
    }
  }
  
  //compting and marking useless features by putting -1 in nb_match
  int nb_useless = 0;
  for(int i = 0; i < 162336; i++)
  {
    if (feats[i].nb_match < (nb_img/2))
    {
      feats[i].nb_match = -1;
      nb_useless++;
    }
  }
  //creating final list
  feature* important_feats = malloc((162336-nb_useless)*sizeof(feature));
  
  //adding important features to the final list
  int pos = 0;
  for(int i = 0; i < 162336; i++)
  {
    if(feats[i].nb_match != -1)
    {
      important_feats[pos] = feats[i];
      pos++;      
    }
  }
  
  free(feats);
  classifier* k = malloc(sizeof(classifier));
  k -> feats = important_feats;
  k -> length = pos;

  if((162336 - nb_useless) != pos)
    printf("error : nb_useless = %i ; pos = %i ; 162336 - nb_useless = %i\n", nb_useless, pos, 162336 - nb_useless);
  else
    printf("important features extracted...\n");

  return k;    
}







/*

int test_feature(feature* feat)
{
  int i = 1;
  char* path = "faces/face(";

  SDL_Surface *img = load_image(path);
  //display_image(img);
  printf("type = %i\n", feat->type);
  Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
  grey(img, grey_img);
  Uint32* int_img = image_integral(grey_img, img->w, img->h);

  int haar_value = 0;

  switch(feat->type)
  {
    case 1:
      haar_value = haar_f1(int_img, feat->w, ;
      break;

    case 2:
      haar_value = haar_f2(int_img, feat->w, ;
      break;

    case 3:
      haar_value = haar_f3(int_img, feat->w, ;
      break;

    case 4:
      haar_value = haar_f4(int_img, feat->w, ;
      break;

    default :
      haar_value = haar_f5(int_img, feat->w, ;
      break;
  }

  free(grey_img);
  free(int_img);
  return haar_value;
}



feature* compute_variance(feature** db, int nbimg)
{
  feature *result = calloc(162336,sizeof(feature));
  for (int i = 0; i < 162336; i++) {
    int mean = 0;
    feature current = db[1][i];
    for (int j = 0; j < nbimg; j++) {
      mean +=  db[j][i].res;
    }
    mean = mean / nbimg;
    int total = 0;
    for (int j = 0; j < nbimg; j++) {
      db[j][i].res =(db[j][i].res-mean)*(db[j][i].res-mean)/nbimg;
      total += db[j][i].res;
    }
    total = total / nbimg;
    current.res = total;
    *(result + i) = current;
  }
  return result;
}

*/
