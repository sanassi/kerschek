#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelper/SdlHelperFunctions.h" 
#include "Rescaling.h"
#include "Floodfill.h"
#include "Morph.h"
#include "Drawing.h"
#include "Component.h"
#include <string.h>
#include "ArrayConversion.h"
#include "Hough.h"
#include <math.h>

void SetWhiteBackground(SDL_Surface *img)
{
	for (int i = 0; i < img -> w; i++)
	{
		for (int j = 0; j < img -> h; j++)
		{
			put_pixel(img, i, j, SDL_MapRGB(img -> format, 255, 255, 255));
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	
	init_sdl();
	SDL_Surface *img = load_image(argv[1]);
	SDL_Surface *img_copy = copy_image(img);

	int len;
	struct Component *components = GetComponents(img, &len);

	if (!components)
                errx(1, "err");


	for (int i = 0; i < len; i++)
	{
		char name[3];
		sprintf(name, "%hu", (short) i);
		char *res_path;
		int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");

		if (size == -1)
			errx(1, "asprintf()");

		components[i].id = i;

		SaveComponentToBMP(img_copy, &components[i], res_path);

		printf("%i\n", components[i].id);
	}

	// test angle between components

	/*
	int p1_x = components[0].topmost_x, p1_y = components[0].topmost_y;
	int p2_x = components[1].topmost_x, p2_y = components[1].topmost_y;
	int p3_x = components[11].topmost_x, p3_y = components[11].topmost_y;
	
	double angle = (atan2(p3_y - p1_y, p3_x - p1_x) - atan2(p2_y - p1_y, p2_x - p1_x)) * 180 / M_PI;

	printf("%f", angle);
	*/
	return 0;
}
