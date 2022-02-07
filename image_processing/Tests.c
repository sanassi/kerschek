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

void SaveComponentToBMP(SDL_Surface *img, struct Component *c, char *name)
{
	Uint32 pixel;
	//Uint8 r, g, b;

	SDL_Surface *res = SDL_CreateRGBSurface(SDL_HWSURFACE, c -> width, c -> height, 32, 255, 255, 255, 0);

	for (int i = c -> box_origin_x; i < res -> w + c -> box_origin_x; i++)
	{
		for (int j = c -> box_origin_y; j < res -> h + c -> box_origin_y; j++)
		{
			pixel = get_pixel(img, i, j);
			put_pixel(res, i - c -> box_origin_x, j - c -> box_origin_y, pixel);
		}
	}
	

	SDL_Surface *tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, res -> w + 40, res -> h + 40, 32, 255, 255, 255, 0);

	for (int i = 0; i < tmp -> w; i++)
	{
		for (int j = 0; j < tmp -> h; j++)
		{
			put_pixel(tmp, i, j, SDL_MapRGB(img -> format, 255, 255, 255));
		}
	}
	for (int i = 0; i < res -> w; i++)
	{
		for (int j = 0; j < res -> h; j++)
		{
			pixel = get_pixel(res, i, j);
			put_pixel(tmp, i + 20, j + 20, pixel);
		}
	}


	SDL_SaveBMP(NearestNeighbourScale(tmp, 28, 28), name);
	free(res);
	free(tmp);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
                return 1;

        init_sdl();


        SDL_Surface *img = load_image(argv[1]);

	double *imgArr = BW_BitmapToArray(img);

	if (!imgArr)
		errx(1, ":/");


	return 0;
}

/*
int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	init_sdl();
	SDL_Surface *img = load_image(argv[1]);
//	SDL_Surface *edges = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 0, 0, 0, 0);

	BoxBlur(img);
	Grayscale(img);
	Binarize(img);
	SDL_Surface *img_copy = copy_image(img);
	SDL_Surface *img_copy_2 = copy_image(img);// copy of img to see the components in image


	SDL_SaveBMP(img, "bin.jpeg");

	Uint32 pixel;
	Uint8 r, g, b;

	struct Component components[1000]; // array of components : TODO : find a way to get adjustable size
	//struct Component candidates[100];
	int a = 0; // index to loop over components array

	Uint32 color = SDL_MapRGB(img -> format, 0, 255, 0);


	for (int i = 0; i < img -> w; i++)
	{
		for (int j = 0; j < img -> h; j++)
		{
			pixel = get_pixel(img, i, j);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && a < 1000)
			{
				struct Component *c = GetComponent(img, i, j);

				if (c -> points -> size > 100)
				{
					//components[a] = *c;
					
		                        //bounding box
					if (((float)(c -> width) / ((float)c -> height)) < 1) // aspect ratio
					{
						components[a] = *c;
						DrawRectangle(img_copy, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);

						// save components in folder
						// use str cat to create the img path

						char name[10];
						sprintf(name, "%i", a);


						char dir[50] = "components/";
						char *path = strcat(dir, name);

						char ext[5] = ".bmp\0";

						char *res_path = strcat(path, ext);


						SaveComponentToBMP(img_copy_2, c, res_path);
						a++;
					}
				}
			}

		}
	}

	if (components == NULL)	
		printf(" ");
	
	
	SDL_SaveBMP(img_copy, "res.bmp");

	return 0;
}
*/
