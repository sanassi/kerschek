#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelperFunctions.h" 
#include "Rescaling.h"
#include "Drawing.h"
#include "Component.h"
#include <string.h>
#include <math.h>
#include "Vector.h"
#include "Morph.h"
#include <unistd.h>

//#include <gstring.h>
#include <glib/gprintf.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "Video.h"
#include "PlateFromImage.h"
#include <limits.h>



int main(int argc, char *argv[])
{
	if (argc != 3)
                errx(1, "Invalid Argument Number");

	MakeDir("frames");
	MakeDir("components");

	if (!strcmp(argv[1], "-v"))
	{
		if (argc != 3)
			errx(1, "Invalid Argument Number");

		if (g_str_has_suffix(argv[2], ".mp4") == FALSE)
		{
			errx(1, "Invalid File Type (.mp4 required)");
		}

		ReadVideo(argv[2]);

	}

	if (!strcmp(argv[1], "-i"))
	{
		if (g_str_has_suffix(argv[2], ".mp4"))
			errx(1, "Invalid File Type (load image)");

		SDL_Surface *img = load_image(argv[2]);

        	PlateDetectionArgs plateArgs =
        	{
                	.angle = 3,
                	.max_h = img -> h / 3,
                	.min_h = 30,
                	.max_w = img -> w / 3,
                	.min_w = 10,
                	.max_ratio = 1,
                	.min_ratio = 0.2,
        	};

        	char *plate = GetPlateFromImage(argv[2], &plateArgs);

        	printf("\nYour Plate : %s !\n", plate);
	}

	/*Remove temporary files*/
	char to_rmv[20][30] = {"res.bmp", "scaled.bmp", "test.bmp",
                                "plate_img.bmp", "final_resized.bmp",
                                "0", "1", "2", "3", "4", "5", "6",
                                 "test_build_plate.bmp", "\0"};

        for (int i = 0; strcmp("\0", to_rmv[i]); i++)
                remove(to_rmv[i]);

	return 0;
}
