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

char *GetPlateAsString(char *path)
{
	init_sdl();
	SDL_Surface *img = load_image(path);
	SDL_Surface *img_copy = load_image(path);
	SDL_Surface *res = load_image(path);

	PreProcess(img, 3, 0, 0);
	

	
	 //struct Component *GetComponents(SDL_Surface *img,
           //     int *len, int max_h, int max_w, int min_h, int min_w, int min_size,
           //     float max_ratio, float min_ratio);
	 

	int len;
	// TODO : use struct component hint  as arg to get components
	struct Component *components = GetComponents(img, &len, img -> h / 2, img -> w / 3, 30, 10, 50, 1, 0);

	if (!components)
                errx(1, "err");

	for (int i = 0; i < len; i++)
	{
		components[i].id = i;
	}

	// cluster : set of "colinear" components

	// ok values
	// angle val 3
	// angle val 1
	// agnle val 2
	struct vector *current_cluster = GetColinearComponents(components, &len, 2);

	SortComponentVector(current_cluster, components, current_cluster -> size);

	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);
	struct Component *c;
	
	Binarize(img_copy);
	
	for (int i = 0; i < (int) current_cluster -> size; i++)
	{
		c = &components[*(current_cluster -> data + i)];
		DrawRectangle(res, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);

		// build path to save bitmap
		char name[3];
                sprintf(name, "%hu", (short) i);
                char *res_path;
                int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");
		//

		if (size == -1)
			printf("rip:/");

		//SaveComponentToBMP(img_copy, c, res_path);
		SaveComponentToBMP_2(c, res_path);

		// use gocr to recog characters
		int pid = fork();
		fflush(stdout);

		if (pid == 0)
		{
			execlp("gocr", "gocr", "-o",name, res_path, (char *) NULL);
			exit(0);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		// end gocr
	}

	SDL_SaveBMP(res, "final.bmp");

	// read digits
	//
	
	char *plate = malloc(7 * sizeof(char));
	char number[2];

	for (int i = 0; i < 7; i++)
	{
		sprintf(number, "%hu", (short) i);

		FILE *fp = fopen(number, "r");
		plate[i] = toupper(fgetc(fp)); // so all char are uppercase
        	fclose(fp);
	}
	
	return plate;
}

int main(int argc, char *argv[])
{
	/*
	if (argc > 0 && argv)
		printf("\n");

	ReadVideo();
	*/
	
	
	if (argc != 2)
		return 1;
	
	char *plate = GetPlateAsString(argv[1]);
	
	printf("\n%s\n", plate);
	return 0;
}
