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

/*	
	int angle = 3;

	for (int i = 1; i < argc; i++)
	{
		char *plate = GetPlateFromImage(argv[i], angle);
        	printf("\n%s\n", plate);
		getchar();
	}
*/	
//	char *plate = GetPlateFromImage(argv[1], 2);	
	//printf("%s\n", plate);


	ReadVideo(argv[1]);

	
	return 0;
}

