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

void SetWhiteBackground(SDL_Surface *img)
{
	for (int i = 0; i < img -> w; i++)
	{
		for (int j = 0; j < img -> h; j++)
		{
			put_pixel(img, i, j, SDL_MapRGB(img -> format, 255, 255, 255));
		}
	}
}

double AngleBetweenComponents(struct Component *c1, struct Component *c2, struct Component *c3)
{
	// computes angle between vectors c1 -> c2 and c1 -> c3
	// plate numbers are usually colinear
	
	int p1_x = c1 -> topmost_x, p1_y = c1 -> topmost_y;
        int p2_x = c2 -> topmost_x, p2_y = c2 -> topmost_y;
        int p3_x = c3 -> topmost_x, p3_y = c3 -> topmost_y;

        double angle = (atan2(p3_y - p1_y, p3_x - p1_x) - atan2(p2_y - p1_y, p2_x - p1_x)) * 180 / M_PI;

	return angle;

}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;

	
	init_sdl();
	SDL_Surface *img = load_image(argv[1]);
	SDL_Surface *img_copy = copy_image(img);
	SDL_Surface *res = copy_image(img);

	int len;
	struct Component *components = GetComponents(img, &len);

	SDL_SaveBMP(img, "dilated_img.bmp");

	if (!components)
                errx(1, "err");


	for (int i = 0; i < len; i++)
	{
		char name[3];
		sprintf(name, "%hu", (short) i);
		char *res_path;
		int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");

		if (size == -1)
			errx(1, "asprintf()");

		components[i].id = i;

		//SaveComponentToBMP(img_copy, &components[i], res_path);

		printf("%i\n", components[i].id);
	}


	// cluster : set of "colinear" components
	struct vector *current_cluster = vector_new();

	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			for (int k = j + 1; k < len; k++)
			{
				double angle = AngleBetweenComponents(&components[i], &components[j], &components[k]);
				
				if (fabs(angle) < 3)
				{
					vector_push(current_cluster, components[k].id);
					printf("%f\n", angle);
					printf("colinear !\n");
					
					if (current_cluster -> size == 5)
						break;
				}
			}

			if (current_cluster -> size == 5)
			{
				vector_push(current_cluster, components[j].id);
				break;
			}
		}

		if (current_cluster -> size == 6)
		{
			vector_push(current_cluster, components[i].id);
			break;
		}

		current_cluster -> size = 0;
	}


	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);
	struct Component *c;
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

	}

	SDL_SaveBMP(res, "final.bmp");

	return 0;
}
