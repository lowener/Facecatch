void detect_faces(SDL_Surface *img)
{
  Uint32* pixels = malloc(img->w*img->h*sizeof(Uint32));
  grey(img, pixels);

  //Loading Strong Classifier
  strong_classif* sc = malloc(sizeof(strong_classif));
  sc->w = malloc(250*sizeof(weak_classif));
  for(int m = 0; m < 250; m++)   
    sc->w[m].d = malloc(sizeof(decision));  
  load_classif(sc);
  float res = 0;

  SDL_Surface* img_sel = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                              24,24,32,0,0,0,0);


  //Selection Scaling
  for(int e = 24; e < min(img->w, img->h); e+=4)
  {
    //Image Browsing
    for(int y = 0; y < img->w - e; y+=5)
    {
      for(int x = 0; x < img->h - e; x+=5)
      {
         //Extracting Selection
         Uint32* selection = malloc(e*e*sizeof(Uint32));
         for(int j = 0; j < e; j++)
         {
            for(int i = 0; i < e; i++)
            {
              *(selection + i + j*e) = *(pixels + x+i + img->w*(y+j));
              //selection[i][j] = *(pixels + x+i + img->w*(y+j));
                SDL_Surface* img_reduced = Stretchblit(img_sel);              
              Uint32* reduced_select = malloc(24*24*sizeof(Uint32));
              for(int b = 0; b < 24; b++)
              {
                for(int a = 0; a < 24; a++)
                {   
                    *(reduced_select + a + (24*b)) = getpixel(img_reduced, a, b);
                }
              }


              free(selection);
              reduced_select = image_integral(reduced_select, 24, 24);
              //Generating database on selection
              feature* database = malloc(162336*sizeof(feature));
              database = haar_features(reduced_select, e, 0, 0);
              free(reduced_select);
              



              //Applying Classifier
              for(int f = 0; f < sc->length; f++)
              {
                if(database[sc->w[f].d->index].res > sc->w[f].d->threshold)
                  res += sc->w[f].coef;
                else
                  res += -sc->w[f].coef;

              }

              //Showing Result
              if(my_abs(res) < 0.45)
                draw_maybe(img, x, y, e);
              else if (res > 0)
                draw_square(img, x, y, e);
              free(database);
              SDL_FreeSurface(img_reduced);
            }
         }
      }
    }
  }
  SDL_FreeSurface(img_sel);

}

