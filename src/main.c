#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "image_processing/Sobel.h"
#include "image_processing/Blur.h"
#include "image_processing/PreProcessing.h"
#include "image_processing/SdlHelperFunctions.h" 
#include "image_processing/Rescaling.h"
#include "image_processing/Floodfill.h"
#include "image_processing/Drawing.h"
#include "image_processing/Component.h"
#include "image_processing/ArrayConversion.h"
#include "image_processing/Hough.h"
#include "image_processing/Vector.h"
#include "image_processing/Morph.h"
#include "image_processing/Video.h"

#include "image_processing/PlateFromImage.h"

#define ANGLE 3

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	
	char *plate = GetPlateFromImage(argv[1], ANGLE);
	
	printf("\n%s\n", plate);

	printf("Is Ok : %s", PlateIsOk(plate) == 0 ? "True" : "False");

	return 0;
}
