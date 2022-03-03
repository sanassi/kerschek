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

/*
int main(int argc, char *argv[])
{
	init_sdl();

	if (argc > 2)
		errx(1, "error : argc");

	SDL_Surface *img = load_image(argv[1]);

	BoxBlur(img);
	BoxBlur(img);
	BoxBlur(img);
	BoxBlur(img);
//	BoxBlur(img);
//        BoxBlur(img);
//        BoxBlur(img);


        Grayscale(img);
        Binarize(img);

	SDL_SaveBMP(img, "proc.bmp");


	SDL_Surface *edges = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 0, 0, 0, 0);

	SobelEdgeDetection(img, edges, 1.5);

	Invert(edges);


	for (int i = 0; i < 12; i++)
	{
		Dilation(edges);
//		Erosion(edges);
	}

	SDL_SaveBMP(edges, "edges.bmp");


	int len;
        
	struct Component *components = GetComponents(edges, &len, img -> h, img -> w, 50, 10, 0, 6, 2);
	
//	struct Component *components = GetComponents(edges, &len, img -> h, img -> w, 30, 10, 100, 1, 0);


	printf("%i", len);

	if (!components)
		return 1;



	SDL_SaveBMP(edges, "sobel.bmp");
	SDL_SaveBMP(img, "dilation.bmp");

	return 0;
}
*/
