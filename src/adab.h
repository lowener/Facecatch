#ifndef ADAB_H_
#define ADAB_H_
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "haar_features.h"


typedef struct decision {
    int toggle, margin,index;
    float threshold,error;
} decision;

typedef struct weak_classif {
    decision *d; // not a vector
    float coef;
} weak_classif;

typedef struct strong_classif {
    weak_classif *w; //vector
    int length;
} strong_classif;


feature *sorting(feature **database, int index, int nbimg );

strong_classif *adaboost(feature **database, int nb_img, int nb_training_rounds,
                         int *prob_weight_img);

#endif /* !ADAB_H_ */
