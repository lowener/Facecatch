#include "sdl_functions.h"

int main(int argc, char *argv[])
{
   if (argc < 2)
      return 1;
   facial_recognition(argv[1]);
}
