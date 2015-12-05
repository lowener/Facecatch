#include "training.h"
#include <string.h>
#include <assert.h>

//@params: nb_img (>0)
feature** init_db(int nb_img, int pos_img, int neg_img, int* prob_weight_img)
{
  feature** database = calloc(nb_img*162336,sizeof(feature));
  assert(database);
  int i = -3;
  const char *pos = "./pos/";
  const char *neg = "./neg/";
  DIR* rep = opendir(pos);
  if (!rep)
    err(1,"Error opening directory, program abort");

  struct dirent *ent;
  while ((ent = readdir(rep)) != NULL && i < pos_img)
  {
    i++;
    if (i < 0)
      continue; // Dodge ./ and ../
    const char *k = ent->d_name;
    char s[strlen(ent->d_name) + 7];
    strcpy(s, "./pos/");
    strcat(s,k);

    SDL_Surface *img = load_image(s);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);

    *(database + i) = haar_features(int_img, img, 0, 0);
    SDL_FreeSurface(img);
    free(grey_img);
    free(int_img);
  }
  printf("%d positive images loaded\n", i);

  for (int j = 0; j < pos_img; j++)  // INIT PROB_WEIGHT
      prob_weight_img[j] = 1;
  for (int j = pos_img; j < pos_img + neg_img; j++)
    prob_weight_img[j] = -1;

  rep = opendir(neg);
  if (!rep)
    err(1,"Error opening directory, program abort");

  i = -3;

  while ((ent = readdir(rep)) != NULL && i < neg_img)
  {
    i++;
    if (i < 0)
      continue; // Dodge ./ and ../
    const char *k = ent->d_name;
    char s[100];
    strcpy(s, neg);
    strcat(s,k);

    SDL_Surface *img = load_image(s);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);

    *(database + pos_img+i) = haar_features(int_img, img, 0, 0);
    SDL_FreeSurface(img);
    free(grey_img);
    free(int_img);
  }
  closedir(rep);
  printf("%d negative images loaded\n", i);
  return database;
}

/*
    SDL_Surface *img = load_image(path);
    Uint32* grey_img = malloc(sizeof(Uint32)*img->w*img->h);
    grey(img, grey_img);
    Uint32* int_img = image_integral(grey_img, img->w, img->h);

    *(database + i - 1) = haar_features(int_img, img, 0, 0);

    free(grey_img);
    free(int_img);
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
/*
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
*/
/*
int class_error(float weight_vect[],int attente[], classifier *c, int nbimg)
{
  int res = 0;
  for (int i = 0; i < nbimg; i++) {
    if (attente[i] != applyclassifier()) {

    }
      res += weight_vect[i]
  }

}
*/

/* harmonize
 * As parameters: Vector of the weight of the image,
 *                vector of the modification(0/1), nb img
 * Harmonize the weight of the image
 * Return the new Vector of weight
 */
/*
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
*/

/*
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
*/

/*
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
*/

/*
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
*/

/*
this function generates a new classifier from the previous one.
nb_features is the number of features wanted in the new classifier.
This new classifier is also saved in file.
*/

/*
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

  write_vector(new_k->feats, new_k->length, "data/classifier.fc");
  printf("Classifier saved in data/classifier.fc\n");
  return new_k;
}
*/




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
