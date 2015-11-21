#include "adab.h"
#include <math.h>


int partition(feature *tableau, int p, int r) {
  int pivot = tableau[p].res;
  int i = p-1;
  int j = r+1;
  feature temp;
  while (1) {
    do
      j--;
    while (tableau[j].res > pivot);

    do
      i++;
    while (tableau[i].res < pivot);

    if (i < j) {
      temp = tableau[i];
      tableau[i] = tableau[j];
      tableau[j] = temp;
    }
    else
      return j;
  }
}

void quickSort(feature *tableau, int p, int r) {
  int q;
  if (p < r) {
    q = partition(tableau, p, r);
    quickSort(tableau, p, q);
    quickSort(tableau, q+1, r);
  }
}

/*Sort feature by their score
 *index = feature n°index
 *nbimg = nb img in your db
 *Returns array of the feature number X
 */
feature *sorting(feature **database, int index, int nbimg)
{
  feature *fimg = malloc(nbimg * sizeof(feature));
  for(int j = 0;j<nbimg;j++)
    fimg[j] = database[j][index];
  quickSort(fimg,0,nbimg-1);
  return fimg;
}

/*feats: array of (nbimg) feats sorted by index then by score
 * weight_img: array of weight (0/1) for (negative/positive) img
 *REMINDER
 *feature = x
 *distrib_poids = y
 *prob_weight_img = w  also called expected output (0/1)
 */
decision *decision_stump(feature *feats, int nbimg, int *distrib_poids,
                         float *prob_weight_img)
{
  //INITIALIZATION
  float threshold = (float)feats[0].res-1;
  int margin = 0;
  float error = 2;
  int toggle;
  float nb_pos_weight_bigger = 0,nb_neg_weight_bigger = 0;
  float nb_pos_weight_smaller = 0,nb_neg_weight_smaller = 0;
  for (int i = 0;i<nbimg;i++)
  {
    if (distrib_poids[i] == 1)
      nb_pos_weight_bigger += prob_weight_img[i];
    else
      nb_neg_weight_bigger+= prob_weight_img[i];
  }

  //Core program
  int j=0, MG=margin, curr_toggle;
  float TH=threshold;
  float pos_error, neg_error, curr_error;
  while (1)
  {
    pos_error = nb_pos_weight_smaller + nb_neg_weight_bigger;
    neg_error = nb_neg_weight_smaller + nb_pos_weight_bigger;//Things we want

    if (pos_error < neg_error) {
      curr_error = pos_error;
      curr_toggle = 1;
    }
    else {
      curr_error = neg_error;
      curr_toggle = 0;
    }
    if (curr_error < error || curr_error == error && MG > margin){
      error = curr_error;
      threshold = TH;
      margin = MG;
      toggle = curr_toggle;
    }
    if (j == nbimg)
      break;
    j++;
    while (1)
    {
      if (feats[j].weight== -1) {
        nb_pos_weight_smaller -= distrib_poids[j];
        nb_neg_weight_smaller += distrib_poids[j];
      }
      else {
        nb_pos_weight_bigger -= distrib_poids[j];
        nb_neg_weight_bigger += distrib_poids[j];
      }
      if (j == nbimg-1 || feats[j].res != feats[j+1].res)
        break; // check if the next feature is similar
      else
        j++;
    }
    if (j==nbimg)
    {
      TH = (float)feats[nb_img - 1].res + 1;
      MG = 0;
    }
    else
    {
      TH = ((float)feats[j].res + (float)feats[j+1].res)/2;
      MG = feats[j+1].res - feats[j].res;
    }
  }

  decision *d = malloc(sizeof(decision));
  d->threshold = threshold;
  d->toggle = toggle;
  d->error = error;
  d->margin = margin;
  return d;
}

decision *best_decision(feature **database, int nbimg, int *distrib_poids,
                        float *prob_weight_img)
{
  decision *best = malloc(sizeof(decision));
  best->error = 2;
  for(int i = 0;i<162336;i++)
  {
    feature *sorted_feats = sorting(database,i ,nbimg);
    decision *d = decision_stump(sorted_feats,nbimg, distrib_poids, prob_weight_img);
    d->index = i;
    if (d->error < best->error || (d->error == best->error && d->margin > best->margin))
    {
      best = d;
    }
    free(sorted_feats);
  }
  return best;
}

static inline int compare(feature f1, feature f2)
{
  return (f1.type==f2.type && f1.w==f2.w && f1.h==f2.h && f1.i ==f2.i && f1.j==f2.j)
}

int apply_classifier(classifier *c, feature *f)
{
  int res =0;
  for (int i = 0; i < c->length; i++) {
    for (int j = 0; j < 162336; j++) {
      if (compare(c->feats[i],f[j]))
        res += f[j].res;
    }
  }
}

static inline
int apply_decision(feature **database, decision *d,int index_img)
{
  if (d->toggle && database[index_img][d->index].res >= d->threshold &&
      database[index_img][d->index].res < d->threshold)
    return 1;
  else
    if (!d->toggle && database[index_img][d->index].res < d->threshold &&
        database[index_img][d->index].res >= d->threshold)
      return -1;
  return 0;
}
/* Current state
 * How to use decision ??
 * Is decision applied to only 1 feature ? NO
 * GL
 */

void adaboost(feature **database, int nb_img, int nb_training_rounds,
              int *prob_weight_img)
{
  float distrib_poids[nb_img];
  for (int i = 0; i < nb_img; i++)
    distrib_poids[i] = 1/(float)nb_img;
/*
  162336;
  for (int i = 0; i < 162336; i++) // Initialize classifier
    c->feats[i] = database[0][i];
*/
  classifier *c = malloc(sizeof(classifier));
  c->feats = malloc(sizeof(feature)*nb_training_rounds;
  c->length = nb_training_rounds;
  c->coef = malloc(sizeof(float)*nb_training_rounds);
  for (int i = 0; i < nb_training_rounds; i++) 
  {
    decision *d = best_decision(database,nb_img,distrib_poids,prob_weight_img);
    float classif_error = 0;
    for (int j = 0; j < nb_ing; j++) 
    {
      if (apply_decision(database,d,j) == 1) 
      {
        classif_error += prob_weight_img[j];
      }
    }
    if (!classif_error && t == 1)
      return; /*line 7*/
    else
    {
      float alpha = 0.5*(float)log((1-(double)classif_error)/(double)classif_error);
      for (int j = 0; j < nb_img; j++) 
      { // Do Zt and H(x)
/*        float k = 0;
        if (apply_decision(database,d,j) == 1)
          k = 1/classif_error;
        else
        k = 1/(1-classif_error);*/
        distrib_poids[j] = distrib_poids[j] * (float)exp(-(double)alpha*
                                                         apply_decision(database,d,j
      }
      

    }
  }
  

}
