#ifndef DATABASE_H_
#define DATABASE_H_



struct S_feature feature;

struct  S_feature
{
  int type;
  int i;  // x position
  int j;  // y position
  int w;  // width
  int h;  // height
  int res;
} S_feature;


void write(feature feats, size_t size, char* fichier);

void read(feature feats, size_t size, char* fichier);


#endif /* !DATABASE_H_ */
