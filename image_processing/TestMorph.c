#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelper/SdlHelperFunctions.h"
#include "Rescaling.h"
#include "Floodfill.h"
#include "Drawing.h"
#include "Component.h"
#include <string.h>
#include "ArrayConversion.h"
#include "Hough.h"
#include <math.h>
#include "Vector.h"
#include <err.h>

#include "Morph.h"


int main(int argc, char *argv[])
{
	init_sdl();

	if (argc > 2)
		errx(1, "error : argc");

	SDL_Surface *img = load_image(argv[1]);

	BoxBlur(img);
        Grayscale(img);
        Binarize(img);


	SDL_Surface *edges = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 0, 0, 0, 0);

	SobelEdgeDetection(img, edges, 1.5);

	Invert(edges);

	for (int i = 0; i < 1; i++)
	{
		Erosion(edges);
	}

	for (int i = 0; i < 10; i++)
	{
		Dilation(edges);
	}


	SDL_SaveBMP(edges, "sobel.bmp");

	SDL_SaveBMP(img, "dilation.bmp");


	return 0;
}
