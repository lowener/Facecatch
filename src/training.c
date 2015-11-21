#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
//#include <math.h>
#include "haar_features.h"
#include "integral_image.h"
#include "pixel_operations.h"
#include "training.h"
#include "sdl_functions.h"
#include "save.h"

feature** init_db(int nb_img)
{
  feature** database = malloc(nb_img*162336*sizeof(feature));
  printf("Filling database\n");
  int i;
  for(i = 1; i <= nb_img; i++)
  {
    char path[20];
    strcpy(path, "faces/face(");
    char str[5];
    sprintf(str,"%i", i);
    strcat(path, str);
    strcat(path, ").bmp");
    puts(path);

    SDL_Surface *img = load_image(path);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);

    *(database + i - 1) = haar_features(int_img, img, 0, 0);
    free(grey_img);
    free(int_img);
    kill_image(img);
  }
  printf("Total: %d images loaded\n", i-1);
  return database;
}
feature *extract(classifier *c, int nb)
{
  feature *result = malloc(sizeof(feature));
  *result = c->feats[nb];
  for (int i = nb; i < c->length - 1; i++) {
    c->feats[i] = c->feats[i + 1];
  }
  c->length--;
  return result;
}



/* harmonize
 * As parameters: Vector of the weight of the image,
 *                vector of the modification(0/1), nb img
 * Harmonize the weight of the image
 * Return the new Vector of weight
 */
void harmonize(float weight_vect[], int modif_array[], int nbimg, float pas)
{
  int index = 0;
  int nbmodif = 0;
  for (index = 0; index < nbimg; index++) {
    if (modif_array[index] == 0) {
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
  //return weight_vect;

}


int my_sqrt(int n)
{
  if (n == 0)
    return 0;
  int y = n;
  while(y > n/y)
    y = (y + n/y)/2;
  return y;
}

classifier* get_important_feats(feature** database, int nb_img)
{
  feature* feats = malloc(162336*sizeof(feature));
  for (int i = 0; i < 162336; i++) {
    feats[i] = database[0][i];
  }

  //Init criteria
  for(int j = 0; j < 162336; j++)
  {
    float criteria = 0;
    for(int i = 0; i < nb_img; i++)
    {
      criteria += database[i][j].res;
    }
    database[0][j].criteria = criteria / nb_img; 
  }

  //Init threshold
  for(int j = 0; j < 162336; j++)
  {
    float threshold = 0;
    for(int i = 0; i < nb_img; i++)
    {
      threshold += (database[i][j].res - database[0][j].criteria) *
                   (database[i][j].res - database[0][j].criteria);
    }
    threshold = threshold / (float)(nb_img);
    database[0][j].threshold = my_sqrt(threshold); 
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
    printf("error : nb_useless = %i ; pos = %i ; 162336 - nb_useless = %i\n",
           nb_useless, pos, 162336 - nb_useless);
  else
    printf("important features extracted...\n");

  return k;
}



// return the feature that match the best in classifier k
//weights = images weights

int get_best(classifier* k, float* weights)
{
  weights[0] += 0;
  int max = 0;
  int maxpos = 0;
  for(int i = 0 ; i < k->length ; i++)
  {
    if(k->feats[i].nb_match > max)
    {
      max = k->feats[i].nb_match;
      maxpos = i;
    }
  }
  return maxpos;
}

/*
this function generates a new classifier from the previous one.
nb_features is the number of features wanted in the new classifier.
This new classifier is also saved in file.
*/

classifier* generate_new_classifier(feature** database, classifier* old_k,
int nb_features, int nb_img)
{
  classifier* new_k = malloc(sizeof(classifier));
  new_k->feats = malloc(nb_features*sizeof(feature));
  new_k->length = nb_features;
  //initializing weight of images vector
  float* weights_img = malloc(nb_img*sizeof(float));
  for(int i = 0; i < nb_img ; i++)
    weights_img[i] = 1/((float)nb_img);

  for (int k = 0; k < nb_features; k++)
  {

    int best = get_best(old_k, weights_img);

    feature* best_feat =  extract(old_k, best);
    new_k->feats[k] = *best_feat;

    //generating modif_array
    int* modif_array = malloc(nb_img*sizeof(int));
    for(int i = 1; i < nb_img ; i++)
    {
      if((database[i][best_feat->index]).res > 0)
        modif_array[i] = 1;
      else
        modif_array[i] = 0;
    }

    //updating weights
    harmonize(weights_img, modif_array, nb_img, 5/nb_img);
    free(modif_array);
    free(best_feat);
  }
  /*  for (int i = 0; i < 10; i++) {
 *  printf(" Weight of image %d : %5f\n", i, weights_img[i]);
 *}
 */
  write_vector(new_k->feats, new_k->length, "data/classifier.fc");
  printf("Classifier saved in data/classifier.fc\n");
  free(weights_img);
  return new_k;
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



//list of features matching negative images
/*
feature* neg_matching features(int nb_img)
{
  feature** database = malloc(nb_img*162336*sizeof(feature));
  printf("Negative Database allocated...\n");
  printf("Filling negative database\n");

  for(int i = 1; i <= nb_img; i++)
  {
    char path[30];
    strcpy(path, "faces/negative(");
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



  return database;
}
*/


