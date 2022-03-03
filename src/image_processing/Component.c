#include "Component.h"

//TODO : change way components saved, so i dont use the src img
void SaveComponentToBMP(SDL_Surface *img, struct Component *c, char *name)
{
	Uint32 pixel;
	//Uint8 r, g, b;

	SDL_Surface *res = SDL_CreateRGBSurface(SDL_HWSURFACE, c -> width, c -> height, 32, 0, 0, 0, 0);

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

struct Component *GetComponent(SDL_Surface *img, int x, int y)
{
	struct Component *c = malloc(sizeof(struct Component));
	c -> points = vector_new();

	Uint32 pixel;
	Uint32 redPixel = SDL_MapRGB(img -> format, 255, 0, 0);
	Uint8 r, g, b;

	struct vector *q = vector_new();

	// correction :vector used as a stack here (not as a queue "q")
	vector_push(q, x);
	vector_push(q, y);

	put_pixel(img, x, y, redPixel);

	// store extreme points from component; useful to get the height and width
	int lm_x = img -> w - 1, lm_y = 0; // lm : leftmost
	int rm_x = 0, rm_y = 0;
	int tm_x = 0, tm_y = img -> h - 1;
	int bm_x = 0, bm_y = 0;
	//

	while (vector_isEmpty(q) == 0)
	{
		vector_pop(q, &y);
		vector_pop(q, &x);

		if (x < lm_x)
		{
			lm_x = x;
			lm_y = y;
		}

		if (x > rm_x)
		{
			rm_x = x;
			rm_y = y;
		}

		if (y < tm_y)
		{
			tm_y = y;
			tm_x = x;
		}

		if (y > bm_y)
		{
			bm_y = y;
			bm_x = x;
		}

		vector_push(c -> points, x);
		vector_push(c -> points, y);

		if (x + 1 < img -> w)
		{
			pixel = get_pixel(img, x + 1, y);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
			{
				vector_push(q, x + 1);
				vector_push(q, y);
				put_pixel(img, x + 1, y, redPixel);
			}
		}

		if (x - 1 >= 0)
		{
			pixel = get_pixel(img, x - 1, y);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
			{
				vector_push(q, x - 1);
				vector_push(q, y);
				put_pixel(img, x - 1, y, redPixel);

			}
		}

		if (y + 1 < img -> h)
		{
			pixel = get_pixel(img, x, y + 1);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
			{
				vector_push(q, x);
				vector_push(q, y + 1);
				put_pixel(img, x, y + 1, redPixel);

			}
		}

		if (y - 1 >= 0)
		{
			pixel = get_pixel(img, x, y - 1);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && g == 0 && b == 0)
			{
				vector_push(q, x);
				vector_push(q, y - 1);
				put_pixel(img, x, y - 1, redPixel);

			}
		}
	}

	c -> rightmost_x = rm_x;
	c -> leftmost_x = lm_x;
	c -> topmost_x = tm_x;
	c -> bottommost_x = bm_x;

	c -> rightmost_y = rm_y;
        c -> leftmost_y = lm_y;
        c -> topmost_y = tm_y;
        c -> bottommost_y = bm_y;

	c ->  height = c -> bottommost_y - c -> topmost_y;
        c ->  width = c -> rightmost_x - c -> leftmost_x;

        c -> box_origin_x = c -> leftmost_x;
        c -> box_origin_y = c -> topmost_y;

//	vector_free(q);

	return c;
<<<<<<< HEAD

=======
>>>>>>> dd7ad1c7900712bcca26f19ce341826d9e5f982a
}

struct Component *GetComponents(SDL_Surface *img,
                int *len, int max_h, int max_w, int min_h, int min_w, int min_size,
		float max_ratio, float min_ratio)
{
	SDL_Surface *img_copy = copy_image(img);
	
	Uint32 pixel;
	Uint8 r, g, b;

	int MAX_NB = 100;

	struct Component *components = malloc(MAX_NB * sizeof(struct Component)); // array of components : TODO : find a way to get adjustable size

	int count = 0; // index to loop over components array

	Uint32 color = SDL_MapRGB(img -> format, 0, 255, 0);

	for (int i = 0; i < img -> w; i++)
	{
		for (int j = 0; j < img -> h; j++)
		{
			pixel = get_pixel(img, i, j);
			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if (r == 0 && count < MAX_NB)
			{

				struct Component *c = GetComponent(img, i, j);

				// check component size and shape
<<<<<<< HEAD
				if ((int) c -> points -> size > min_size && c -> height < max_h && c -> height > min_h
=======
				if (c -> points -> size > (size_t) min_size && c -> height < max_h && c -> height > min_h
>>>>>>> dd7ad1c7900712bcca26f19ce341826d9e5f982a
						&& c -> width < max_w && c -> width > min_w)
				{
		                        //bounding box
					if (((float)(c -> width) / ((float) c -> height)) < max_ratio &&
							((float)(c -> width) / ((float) c -> height)) > min_ratio) // aspect ratio
					{
						components[count] = *c;

						DrawRectangle(img_copy, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);
						
						c -> id = count;
						count++;
					}
				}
			}
		}
	}

	SDL_SaveBMP(img_copy, "res.bmp");
	SDL_FreeSurface(img_copy);

	*len = count;

	return components;
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

struct vector *GetColinearComponents(struct Component *components, int *len, int min_angle)
{
        struct vector *current_cluster = vector_new();

        for (int i = 0; i < *len; i++)
        {
                for (int j = i + 1; j < *len; j++)
                {
                        for (int k = j + 1; k < *len; k++)
                        {
                                double angle = AngleBetweenComponents(&components[i], &components[j], &components[k]);

                                if (fabs(angle) < min_angle)
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
        return current_cluster;
}

void free_component(struct Component *c)
{
	vector_free(c -> points);
	free(c);
}
