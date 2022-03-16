#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelperFunctions.h" 
#include "Rescaling.h"
#include "Floodfill.h"
#include "Drawing.h"
#include "Component.h"
#include <string.h>
#include "ArrayConversion.h"
#include "Hough.h"
#include <math.h>
#include "Vector.h"
#include "Morph.h"
#include <unistd.h>
#include <sys/wait.h>
#include "Video.h"
#include "PlateFromImage.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	//int angle = 3;

	/*
	for (int i = 1; i < argc; i++)
	{
		char *plate = GetPlateFromImage(argv[i], angle);
        	printf("\n%s\n", plate);
		getchar();
	}
//	char *plate = GetPlateFromImage(argv[1], 2);	
	*/

	SDL_Surface *img = load_image(argv[1]);
	SDL_Surface *screen;

	screen = display_image(img);
	update_surface(screen, img);
	wait_for_keypressed();

	PreProcess(img, 3, 0, 0);

	screen = display_image(img);
	update_surface(screen, img);
	wait_for_keypressed();

	char *plate = GetPlateFromImage(argv[1], 3);
	if (plate)
		printf("works");
	SDL_Surface *comp_img = load_image("res.bmp");
	screen = display_image(comp_img);
	update_surface(screen, comp_img);
	wait_for_keypressed();

	SDL_Surface *final = load_image("final.bmp");
	screen = display_image(final);
	update_surface(screen, final);
	wait_for_keypressed();

//	ReadVideo(argv[1]);

	
	return 0;
}

