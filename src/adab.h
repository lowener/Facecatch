#ifndef ADAB_H_
# define ADAB_H_
#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "haar_features.h"


typedef struct decision {
    int toggle, margin,index;
    float threshold,error;
} decision;


feature *sorting(feature **database, int index, int nbimg );

#endif /* !ADAB_H_ */
