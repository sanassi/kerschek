#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void init_sdl()
{
  // Init only the video part.
  // If it fails, die with an error message.
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
  SDL_Surface *img;

  // Load an image using SDL_image with format detection.
  // If it fails, die with an error message.
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
  SDL_Surface *screen;

  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if (screen == NULL)
    {
      // error management
      errx(1, "Couldn't set %dx%d video mode: %s\n",
	   img->w, img->h, SDL_GetError());
    }

  // Blit onto the screen surface
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // return the screen for further uses
  return screen;
}


int main(int argc, char *argv[])
{
  if (argc > 2)
    errx(1, "too many arg");
 
  SDL_Rect position;
  SDL_Surface *rect;
  SDL_Surface *PlateEmpty;
  SDL_Surface *image_surface;
  int x = 350;
  int y = 100; 
  init_sdl();

  char *PlateName = argv[1];
  FILE *f = fopen(PlateName, "r");
  char p[9];
  fgets(p, 8, f);
  
  
  strcat(PlateName, "_IMG.bmp");

  PlateEmpty = load_image("img/plate_empty.png");
  SDL_SaveBMP(PlateEmpty, PlateName);

  fclose(f);

  //size_t l = strlen(p);
  //printf("plate len: %lu\n", l);
  //printf("%d\n", p[6]);

  int tiret = 0;

  for(size_t i = 0; i < 7; i++)
    {
      printf("tiret = %i\n", tiret);
      if (tiret == 2 || tiret == 5)
	{
	  printf("ATTENTION TIRET\n");
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/tiret.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	  x += 150;
	}
      
      if (p[i] == '1')
	{
	  
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/1.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

      else if (p[i] == '2')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/2.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

      else if (p[i] == '3')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/3.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}
       
       else if (p[i] == '4')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/4.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}
      else if (p[i] == '5')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/5.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == '6')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/6.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == '7')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/7.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      
      else if (p[i] == '8')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/8.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

       else if (p[i] == '9')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/9.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'A')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/A.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

       else if (p[i] == 'B')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/B.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'C')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/C.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'D')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/D.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

        else if (p[i] == 'E')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/E.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'F')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/F.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'G')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/G.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'H')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/H.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'I')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/I.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'J')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/J.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'K')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/K.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'L')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/L.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'M')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/M.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'N')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/N.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'O')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/O.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'P')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/P.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'Q')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/Q.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'R')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/R.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      
        else if (p[i] == 'S')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/S.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}

      else if (p[i] == 'T')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/T.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'U')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/U.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'V')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/V.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'W')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/W.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'X')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/X.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

       else if (p[i] == 'Y')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/Y.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}

      else if (p[i] == 'Z')
	{
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/Z.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);
	}
      else
	{
	  printf("c blanc");
	  image_surface = load_image(PlateName);
	  rect = load_image("img/toprint/empty.bmp");

	  position.x = x;
	  position.y = y;

	  SDL_BlitSurface(rect, NULL, image_surface, &position);
	  SDL_SaveBMP(image_surface, PlateName);
	  SDL_FreeSurface(rect);
	  SDL_FreeSurface(image_surface);

	}
      printf("Lettre : %c\n", p[i]);
      x += 150;
      tiret += 1;
    }
  SDL_FreeSurface(PlateEmpty);

  
  
  return 0;
}
