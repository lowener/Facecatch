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
decision *decision_stump(feature *feats, int nbimg, double *distrib_poids,
                         int *prob_weight_img)
{
  //INITIALIZATION
  double threshold = feats[0].res-1;
  int margin = 0;
  double error = 2;
  int toggle = 0;
  double nb_pos_weight_bigger = 0,nb_neg_weight_bigger = 0;
  double nb_pos_weight_smaller = 0,nb_neg_weight_smaller = 0;
  for (int i = 0;i<nbimg;i++)
  {
    if (feats[i].res > threshold)
    {
      if (prob_weight_img[i] == 1)
        nb_pos_weight_bigger += distrib_poids[i];
      else
        nb_neg_weight_bigger+= distrib_poids[i];
    }
  }

  //Core program
  int j=0, MG=margin, curr_toggle;
  double TH=threshold;
  double pos_error, neg_error, curr_error;
  while (1)
  {
    pos_error = nb_pos_weight_smaller + nb_neg_weight_bigger;
    neg_error = nb_neg_weight_smaller + nb_pos_weight_bigger;//Things we want

    if (pos_error <= neg_error) {
      curr_error = pos_error;
      curr_toggle = 0;
    }
    else {
      curr_error = neg_error;
      curr_toggle = 1;
    }
    if (curr_error < error || (curr_error == error && MG > margin)){
      error = curr_error;
      threshold = TH;
      margin = MG;
      toggle = curr_toggle;
    }
    if (j == nbimg-1)
      break;
    j++;
    while (1)
    {
      if (prob_weight_img[j] == -1) {
        nb_neg_weight_bigger  -= distrib_poids[j];
        nb_neg_weight_smaller += distrib_poids[j];
      }
      else {
        if (nb_pos_weight_bigger >= distrib_poids[j])
        {
          nb_pos_weight_bigger  -= distrib_poids[j];
          nb_pos_weight_smaller += distrib_poids[j];
        }
      }
      if (j == nbimg-1 || feats[j].res != feats[j+1].res)
        break; // check if the next feature is similar
      else
        j++;
    }
    if (j==nbimg-1)
    {
      TH = feats[nbimg-1].res + 1;
      MG = 0;
    }
    else
    {
      TH = (feats[j].res + feats[j+1].res)/2;
      MG = feats[j+1].res - feats[j].res;
    }
  }

  decision *d = malloc(sizeof(decision));
  d->threshold = threshold;
  d->toggle = toggle;
  if (error < 0 && toggle)
    error = 0.00000001;
  d->error = error;
  d->margin = margin;
  return d;
}

decision *best_decision(feature **database, int nbimg, double *distrib_poids,
                        int *prob_weight_img, int *feat_selected)
{
  decision *best = calloc(1,sizeof(decision));
  best->error = 2;
  for(int i = 0;i<162336;i++)
  {
    int b = 1;
    for (int j = 0; feat_selected[j] != -1; j++) {
      if (b && i == feat_selected[j])
        b = 0;
    }
    if (b) // to not select twice a feat
    {
      feature *sorted_feats = sorting(database,i ,nbimg);
      decision *d = decision_stump(sorted_feats,nbimg, distrib_poids, prob_weight_img);
      d->index = i;
      if (d->toggle && (d->error < best->error || (d->error == best->error && d->margin > best->margin)))
      {
        free(best);
        best = d;
      }
      free(sorted_feats);
    }
  }
  return best;
}

/*
static inline int compare(feature f1, feature f2)
{
  return (f1.type==f2.type && f1.w==f2.w && f1.h==f2.h && f1.i ==f2.i && f1.j==f2.j);
}
*/

static inline
int apply_decision(feature **database, decision *d,int index_img)
{
  if (d->toggle)
    return (database[index_img][d->index].res >= d->threshold);
  else
    return (database[index_img][d->index].res <  d->threshold);
}

/* Adaboost takes as parameters the db, the nb of img, the number of rounds (T)
 * and the expected output of an image (1/-1)
 *
 * Return an array of (T) weak classifier that have a decision and
 * a coefficient (alpha)
 */

strong_classif *adaboost(feature **database, int nb_img, int nb_training_rounds,
              int *prob_weight_img)
{
  printf("\n");
  double distrib_poids[nb_img];
  for (int i = 0; i < nb_img; i++)
    distrib_poids[i] = 1/nb_img; //weight repartition
  strong_classif *sc = malloc(sizeof(strong_classif));
  sc->length = nb_training_rounds;
  sc->w = malloc(sizeof(weak_classif)*sc->length); //vector of weak classif
  int feat_selected[nb_training_rounds + 1]; // to not take twice a feature

  for (int i = 0; i < nb_training_rounds ; i++)
    feat_selected[i]=0;
  feat_selected[nb_training_rounds] = -1; // last is -1
//START
  for (int i = 0; i < nb_training_rounds; i++) {
    decision *d = best_decision(database,nb_img,distrib_poids,
                                prob_weight_img, feat_selected);

    feat_selected[i] = d->index; //index of feat selected
    sc->w[i].d = d;
    double classif_error = 0;
    for (int j = 0; j < nb_img; j++)
      if (apply_decision(database,d,j) == 1)
        classif_error += distrib_poids[j];

    if (!classif_error && nb_training_rounds == 0)
    {
      sc->w[0].coef = 1;
      return sc;
    }
    else
    {
      double tmp = (1-classif_error)/classif_error;
      double alpha = 0.5*log(tmp);
      double weight_sum = 0;
      for (int j = 0; j < nb_img; j++)
      { //Weight update
        double k = 0;
        if (apply_decision(database,d,j) == 1)
          k = 1;
        else
          k =-1;
        k=exp((double)(-1 * alpha*prob_weight_img[j]*k));
        distrib_poids[j] = distrib_poids[j] * k;
        weight_sum += distrib_poids[j];
      }
      if (weight_sum != 1)
      {
        weight_sum = 1/weight_sum;
        for (int j = 0; j < nb_img; j++) {
          distrib_poids[j] = distrib_poids[j]*weight_sum;
        }
      }
      sc->w[i].coef = alpha;
    }
    printf("\rRound n. %d\n", i);
  }
  return sc;
}
//SAVE CLASSIFIER
