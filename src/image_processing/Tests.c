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

int distSq(int x1, int y1, int z1, int x2, int y2, int z2)
{
	return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);
}

SDL_Surface *FrameDifference(SDL_Surface *img_1, SDL_Surface *img_2)
{
	SDL_Surface *img_1 = load_image("frame_1.png");
        SDL_Surface *img_2 = load_image("frame_2.png");

        SDL_Surface *sub = SDL_CreateRGBSurface(SDL_HWSURFACE, img_1 -> w, img_1 -> h, 32, 0, 0, 0, 0);

        Uint32 pixel_1;
        Uint32 pixel_2;

        Uint32 res_pixel = SDL_MapRGB(img_1 -> format, 255, 255, 255);

        Uint8 r_1, g_1, b_1;
        Uint8 r_2, g_2, b_2;

        int threshold = 100;

        for (int i = 0; i < img_1 -> w; i++)
        {
                for (int j = 0; j < img_1 -> h; j++)
                {
                        pixel_1 = get_pixel(img_1, i, j);
                        pixel_2 = get_pixel(img_2, i, j);

                        SDL_GetRGB(pixel_1, img_1 -> format, &r_1, &g_1, &b_1);
                        SDL_GetRGB(pixel_2, img_2 -> format, &r_2, &g_2, &b_2);

                        int d_Sq = distSq(r_1, b_1, g_1, r_2, g_2, b_2);

                        if (d_Sq > threshold * threshold)
                        {
                                put_pixel(sub, i, j, res_pixel);
                        }
                }
        }

	return sub;
}

int main()
{
	SDL_Surface *img_1 = load_image("frame_1.png");
	SDL_Surface *img_2 = load_image("frame_2.png");

	SDL_Surface *sub = SDL_CreateRGBSurface(SDL_HWSURFACE, img_1 -> w, img_1 -> h, 32, 0, 0, 0, 0);

	Uint32 pixel_1;
	Uint32 pixel_2;

	Uint32 res_pixel = SDL_MapRGB(img_1 -> format, 255, 255, 255);

	Uint8 r_1, g_1, b_1;
	Uint8 r_2, g_2, b_2;

	int threshold = 100;

	for (int i = 0; i < img_1 -> w; i++)
	{
		for (int j = 0; j < img_1 -> h; j++)
		{
			pixel_1 = get_pixel(img_1, i, j);
			pixel_2 = get_pixel(img_2, i, j);

			SDL_GetRGB(pixel_1, img_1 -> format, &r_1, &g_1, &b_1);
			SDL_GetRGB(pixel_2, img_2 -> format, &r_2, &g_2, &b_2);
			
			int d_Sq = distSq(r_1, b_1, g_1, r_2, g_2, b_2);

			if (d_Sq > threshold * threshold)
			{
				put_pixel(sub, i, j, res_pixel);
			}
		}
	}

	SDL_SaveBMP(sub, "sub.bmp");
	return 0;
}
