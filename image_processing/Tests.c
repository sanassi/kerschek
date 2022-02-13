#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelper/SdlHelperFunctions.h" 
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

void PreProcess(SDL_Surface *img, int nbBlur, int nbErode, int nbDilate)
{
	for (int i = 0; i < nbBlur; i++)
		BoxBlur(img);

	Grayscale(img);
        Binarize(img);

	for (int i = 0; i < nbErode; i++)
		Erosion(img);

	for (int i = 0; i < nbDilate; i++)
                Dilation(img);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	
	init_sdl();
	SDL_Surface *img = load_image(argv[1]);
	SDL_Surface *img_copy = load_image(argv[1]);
	SDL_Surface *res = load_image(argv[1]);

	PreProcess(img, 3, 0, 0);

	/*
	 *struct Component *GetComponents(SDL_Surface *img,
                int *len, int max_h, int max_w, int min_h, int min_w, int min_size,
                float max_ratio, float min_ratio);
	 */

	int len;
	struct Component *components = GetComponents(img, &len, img -> h / 2, img -> w / 3, 30, 10, 50, 1, 0);

	if (!components)
                errx(1, "err");

	for (int i = 0; i < len; i++)
	{
		components[i].id = i;
	}

	// cluster : set of "colinear" components

	// agnle val 3
	struct vector *current_cluster = GetColinearComponents(components, &len, 2);


	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);
	struct Component *c;
	
	Binarize(img_copy);
	for (int i = 0; i < (int) current_cluster -> size; i++)
	{
		c = &components[*(current_cluster -> data + i)];
		DrawRectangle(res, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);

		char name[3];
                sprintf(name, "%hu", (short) i);
                char *res_path;
                int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");

		if (size == -1)
			printf("rip:/");

		SaveComponentToBMP(img_copy, c, res_path);

		// use gocr to recog characters
		int pid = fork();		
		if (pid == 0)
		{
			execlp("gocr", "gocr", "-o",name, res_path, (char *) NULL);
			exit(0);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
	}

	SDL_SaveBMP(res, "final.bmp");

	//gocr -o out.txt 5.bmp



	return 0;
}
