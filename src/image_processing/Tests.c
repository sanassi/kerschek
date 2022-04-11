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
#include <sys/types.h>
#include <sys/stat.h>

#include "Video.h"
#include "PlateFromImage.h"

#include <limits.h>

void DrawGrid(SDL_Surface *img, int nb_vert, int nb_hor, Uint32 color)
{
	for (int i = 0; i < img -> w - 1; i += nb_vert)
	{
		DrawLine(img, 0, i, img -> h, i, 2, color);
	}

	for (int i = 0; i < img -> h - 1; i += nb_hor)
	{
		DrawLine(img, i, 0, i, img -> w, 2, color);
	}
}


int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	char *plate = GetPlateFromImage(argv[1], 3);

	printf("%s", plate);

	
	return 0;
}
