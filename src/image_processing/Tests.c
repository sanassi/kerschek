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


// sort components (according to their x pos) to get license plate numbers in the correct order
void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void SortComponentVector(struct vector *v, struct Component *components, int len)
{
	int *data = v -> data;
	int i, j, min_index;
	
	for (i = 0; i < len - 1; i++)
	{
		min_index = i;

		for (j = i + 1; j < len; j++)
		{
			if (components[data[j]].box_origin_x < components[data[min_index]].box_origin_x)
			{
				min_index = j;
			}
		}

		Swap(&v -> data[min_index], &v -> data[i]);
	}
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
	

	
	 //struct Component *GetComponents(SDL_Surface *img,
           //     int *len, int max_h, int max_w, int min_h, int min_w, int min_size,
           //     float max_ratio, float min_ratio);
	 

	int len;
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
	struct vector *current_cluster = GetColinearComponents(components, &len, 3);

	SortComponentVector(current_cluster, components, current_cluster -> size);

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
			
			printf("ok");
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

	return 0;
}
