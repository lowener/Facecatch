#ifndef TRAINING_H_
#define TRAINING_H_


feature** init_db(int nb_img);

float *harmonize(float weight_vect[], int modif_array[], int nbimg);

feature* get_weights(feature** database, int nb_img);

//feature* compute_variance(feature** db, int nbimg);

//int test_feature(feature* feat);

#endif
