#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>


int near(float x)
{
  int a = floor(x);
  if (a - x > 0.5)
    a++;
  return a;
}

int min(int a, int b)
{
  if ((int)(*a) < (int)(*b))
    return a;
  return b;
}


int max(int a, int b)
{
  if ((int)(*a) < (int)(*b))
    return b;
  return a;
}


Uint32 *downsample(Uint32 *img, int e)
{
  double phi = 0.6*sqrt(pow((double)e/24,2)-1);
  Uint32 matrix[24][24];
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      float i2 = ((float)e-1)*((float)i+1)/25;
      float j2 = ((float)e-1)*((float)j+1)/25;
      int imax = min(near(i2)+1,e-1);
      int imin = max(0,near(i2));
      int jmax = min(near(j2)+1,e-1);
      int jmin = max(0,near(j2));
      matrix[i][j] = 0.25*(*(img+imax+jmax)+*(img+imin+jmax)+
                           *(img+imin+jmin)+*(img+imin+jmin))
    }

  }

}
