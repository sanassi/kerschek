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




//int main(int argc, char *argv[])
//{
	/*
	SDL_Surface *img = load_image(argv[1]);
	PreProcess(img, 3, 0, 0);
	SDL_SaveBMP(ResizeToFit(img, 700, 700), "resc.bmp");

	*/

	/*	
	if (argc != 2)
		return 1;

	char *plate = GetPlateFromImage(argv[1], 3);

	printf("%s", plate);

	*/

	//SDL_SaveBMP(BuildImageRes("B_46_HN"), "test_build_plate.bmp");
	

	/*
	SDL_Surface *img = load_image(argv[1]);

	PreProcess(img, 3, 0, 0);

	SDL_Surface *edges = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 0, 0, 0, 0);

	SDL_Surface *res = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 0, 0, 0, 0);

	Uint32 blackPixel = SDL_MapRGB(img -> format, 0, 0, 0);
	Uint32 whitePixel = SDL_MapRGB(res -> format, 255, 255, 255);
	for (int i = 0; i < res -> w; i++)
        {
                for (int j = 0; j < res -> h; j++)
                {
                        put_pixel(res, i, j, whitePixel);
                }
        }

	SobelEdgeDetection(img, edges, 1);

	Invert(edges);

	int max_h = img -> h, min_h = 50;
        int max_w = img -> w, min_w = 150;
        int min_size = 10;
        float max_ratio = 10, min_ratio = 2;

	struct Component *c;
	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);

	int len;
        struct Component *components = GetComponents(edges,
                        &len, max_h,
                        max_w, min_h,
                        min_w, min_size,
                        max_ratio, min_ratio);

        if (!components)
                errx(1, "error : components NULL");

		*/

	
	//for (int i = 0; i < len; i++)
	//{
	//	c = &components[i]; // get component from id
                /*
		DrawRectangle(img,
                                c -> box_origin_y,
                                c -> box_origin_x,
                                c -> height,
                                c ->  width,
                                10, color);
		*/

		/*
		for (size_t i = 0; i < c -> points -> size - 2; i += 2)
		{
			put_pixel(res, c -> points -> data[i], c -> points -> data[i + 1], blackPixel);
		}
		*/
	/*
		for (int i = c -> box_origin_x; i < c -> box_origin_x + c -> width; i++)
		{
			for (int j = c -> box_origin_y; j < c -> box_origin_y + c -> height; j++)
			{
				Uint32 pixel;
				pixel = get_pixel(img, i, j);
				put_pixel(res, i, j, pixel);
			}
		}
	}
	

	SDL_SaveBMP(res, "cleared.bmp");


	char *plate = GetPlateFromImage("cleared.bmp", 3);

        printf("%s", plate);

	SDL_SaveBMP(img, "comp.bmp");
	SDL_SaveBMP(edges, "edges.bmp");
	*/

//	return 0;
//}
