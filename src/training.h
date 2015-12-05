#ifndef TRAINING_H_
#define TRAINING_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include "haar_features.h"
#include "integral_image.h"
#include "pixel_operations.h"
#include <err.h>
#include "sdl_functions.h"
#include "save.h"
#include <dirent.h>

feature** init_db(int nb_img, int pos_img, int neg_img, int* prob_weight_img);

//feature *extract(classifier *c, int nb);

//float *harmonize(float weight_vect[], int modif_array[], int nbimg);

feature* get_weights(feature** database, int nb_img);

classifier* get_important_feats(feature** database, int nb_img);

classifier* generate_new_classifier(feature** database, classifier* old_k,
                                    int nb_features, int nb_img);

//feature* compute_variance(feature** db, int nbimg);

//int test_feature(feature* feat);

#endif
