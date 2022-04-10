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


	/*/
	SDL_Surface *img = load_image(argv[1]);
	SDL_Surface *img_cpy = copy_image(img);

	struct Component null_c;
	null_c.id = -1;

	Uint32 color = SDL_MapRGB(img -> format, 0, 255, 0);

	int len;
        struct Component *components = GetComponents(img,
                                &len,
                                INT_MAX,
                                INT_MAX,
                                0,
                                0,
                                0,
                                DBL_MAX,
                                0);

	for (int i = 0; i < len; i++)
                {
                        struct Component *c = &components[i]; // get component from id
                        if (c -> id == -1)
                                continue;


			DrawFillCircle(img_cpy, 
					c -> box_origin_y, 
					c -> box_origin_x,
					4,
					SDL_MapRGB(img_cpy -> format, 255, 0, 0));
			DrawFillCircle(img_cpy,
                                        c -> box_origin_y + c -> height,
                                        c -> box_origin_x + c -> width,
                                        4,
                                        SDL_MapRGB(img_cpy -> format, 255, 0, 0));
                }

	int l = len;
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (Overlap(&components[i], &components[j]) == 1)
			{
				printf("overlap!");
                		struct Component *merge = MergeComponents(&components[i], &components[j]);

                		components[i].id = -1;
                		components[j].id = -1;
                		components[l] = *merge;
                		l += 1;
			}
		}
	}

	len = l;


	for (int i = 0; i < len; i++)
                {

                        struct Component *c = &components[i]; // get component from id
			if (c -> id == -1)
				continue;

                        DrawRectangle(img_cpy,
                                        c -> box_origin_y,
                                        c -> box_origin_x,
                                        c -> height,
                                        c ->  width,
                                        4,
                                        SDL_MapRGB(img_cpy -> format, 0, 0, 255));

			DrawFillCircle(img_cpy,
                                        c -> box_origin_y + (c -> height / 2),
                                        c -> box_origin_x + (c -> width / 2),
                                        4,
                                        SDL_MapRGB(img_cpy -> format, 255, 0, 0));
                }



	SDL_SaveBMP(img_cpy, "res_comp2.bmp");

	*/
	
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

	int block_size = 16;



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


	int nth = 11; // nth block 
	nth -= 1;

	int block_x = 0;
	int block_y = 0;

	while (nth > 0)
	{
		block_x += block_size;
		nth -= 1;
		if ((block_x) == W)
                {
                        block_y += block_size;
                        block_x = 0;
                }
	}

	
	printf("x = %i; y = %i\n", block_x, block_y);
	for (int i = block_y; i < block_size + block_y; i++)
	{
		for (int j = block_x; j < block_size + block_x; j++)
		{
			put_pixel(resized, j, i, SDL_MapRGB(resized -> format, 255, 0, 255));
		}
	}

	DrawGrid(resized, 16, 16, SDL_MapRGB(resized -> format, 0, 255, 0));

	SDL_SaveBMP(resized, "test_block.bmp");

	*/

	/*test on only one histogram*/
	/*
	int nb_bin = 9;
	int bin_step = 20;

	double hist[nb_bin];

	for (int i = block_x; i < block_size + block_x; i++)
	{
		for (int j = block_y; j < block_size + block_y; j++)
		{
			double thet = ang[i * W + j];
			double mu = mag[i * W + j];

			double w = 180 / nb_bin;

			int _j = ( (int) floor((thet / bin_step) - 0.5)) % 9;

			int center = (int) (w * ((_j + 1) + 0.5));

			hist[_j] = mu * ( (center - thet) / w);

			center = (int) (w * _j + 0.5);
			hist[(_j + 1) % 9] = mu * ((thet - center) / w);

			printf("%f\n", hist[_j]);

		}
	}

	for (int i = 0; i < 9; i++)
		printf("%f", hist[i]);


		*/
	return 0;
}
