#ifndef HAAR_FEATURES_H_
#define HAAR_FEATURES_H_

//typedef struct S_feature feature;

typedef struct feature{
    int type;
    int i;
    int j;
    int w;
    int h;
    int res;
    int nbimg;
    int index;
    //float var;
}feature;

typedef struct classifier{
    feature* feats; //array of feature
    float* coef;
    int length;
}classifier;


void build_feat(feature *feat, int type, int i, int j, int w, int h, int res);

feature* haar_features( Uint32 *int_img, int w, int x, int y);

#endif /* !HAAR_FEATURES_H_ */
