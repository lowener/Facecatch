#ifndef HAAR_FEATURES_H_
#define HAAR_FEATURES_H_

//typedef struct S_feature feature;

typedef struct feature{     //WEAK CLASSIFIER STRUCT
  int type;
  int i;
  int j;
  int w;
  int h;
  int res;
  int nb_match;
  float weight;
  int index;
  float error;
  int criteria;
  float threshold;
  //float var;
}feature;

typedef struct classifier{
    feature* feats; //array of features
    int length;
    float *coef;
}classifier;

typedef struct adaboost_img{
  int index;
  float weight;
  int polarity;
}adaboost_img;


void build_feat(feature *feat, int type, int i, int j, int w, int h, int res);

feature *compute_haar(Uint32 *int_img, SDL_Surface *img);

feature* haar_features( Uint32 *int_img, SDL_Surface *img, int x, int y);

int haar_f1 (Uint32 *int_img, size_t width, feature *array_feat,
              feature *current,int index_array, int x, int y);
int haar_f2 (Uint32 *int_img, size_t width, feature *array_feat,
              feature *current,int index_array, int x, int y);
int haar_f3 (Uint32 *int_img, size_t width, feature *array_feat,
              feature *current,int index_array, int x, int y);
int haar_f4 (Uint32 *int_img, size_t width, feature *array_feat,
              feature *current,int index_array, int x, int y);
int haar_f5 (Uint32 *int_img, size_t width, feature *array_feat,
              feature *current,int index_array, int x, int y);

#endif /* !HAAR_FEATURES_H_ */
