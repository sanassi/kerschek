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
	if (argc != 2)
		return 1;

	ReadVideo(argv[1]);
	/*
	char *plate = GetPlateFromImage(argv[1], 3);
	printf("%s", plate);
	*/
	/*
	int W = 64, H = 128;
	SDL_Surface *img = load_image(argv[1]);
	Grayscale(img);
	SDL_Surface *resized = NearestNeighbourScale(img, W, H);


	double gradX[W * H];
	double gradY[W * H];

	double mag[W * H]; // magnitude
	double ang[W * H]; // angle


	Uint32 pixel_1;
	Uint32 pixel_2;
	Uint8 val_1;
	Uint8 val_2;

	int block_size = 8;



	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < W; j++)
		{
			val_1 = 0;
			val_2 = 0;

			if (i + 1 < resized -> h)
			{
				pixel_1 = get_pixel(resized, j, i + 1);
                        	SDL_GetRGB(pixel_1, resized -> format, &val_1, &val_1, &val_1);
			}

			if (i - 1 >= 0)
			{
				pixel_2 = get_pixel(resized, j, i - 1);
                        	SDL_GetRGB(pixel_2, resized -> format, &val_2, &val_2, &val_2);
			}

			gradX[i * W + j] = val_1 - val_2;

			if (j + 1 < resized -> w)
			{
				pixel_1 = get_pixel(resized, j + 1, i);
                        	SDL_GetRGB(pixel_1, resized -> format, &val_1, &val_1, &val_1);
			}

			if (j - 1 >= 0)
			{
				pixel_2 = get_pixel(resized, j - 1, i);
                        	SDL_GetRGB(pixel_2, resized -> format, &val_2, &val_2, &val_2);
			}

                        gradY[i * W + j] = val_1 - val_2;

			double gX = gradX[i * W + j];
			double gY = gradY[i * W + j];

			mag[i * W + j] = sqrt(gX * gX + gY * gY);
			ang[i * W + j] = atan2(gY, gX);
		}
	}

	// cell : 8 x 8 pixels
	// block : 2 x 2 cells


	int nth = 1; // nth block 
	nth -= 1;

	int block_x = 0;
	int block_y = 0;

	while (nth > 0)
	{
		block_x += 8;
		nth -= 1;
		if ((block_x) == W)
                {
                        block_y += 8;
                        block_x = 0;
                }
	}


	
	printf("x = %i; y = %i\n", block_x, block_y);
	for (int i = block_y; i < 8 + block_y; i++)
	{
		for (int j = block_x; j < 8 + block_x; j++)
		{
			put_pixel(resized, j, i, SDL_MapRGB(resized -> format, 0, 255, 0));
		}
	}

	SDL_SaveBMP(resized, "test_block.bmp");

	

	int hist_size = 9;
	int bin_step = 20;

	double hist[hist_size];

	for (int i = block_x; i < block_size + block_x; i++)
	{
		for (int j = block_y; j < block_size + block_y; j++)
		{
			int j_ = floor((ang[i * W + j] / bin_step) - 0.5);

			hist[j_] = 
		}
	}

	*/

	return 0;
}
