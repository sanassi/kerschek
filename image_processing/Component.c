#include "Component.h"

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

}

struct Component *GetComponents(SDL_Surface *img, int *len)
{
	init_sdl();
	
	BoxBlur(img);
	Grayscale(img);
	Binarize(img);
	SDL_Surface *img_copy = copy_image(img);
	SDL_Surface *img_copy_2 = copy_image(img);// copy of img to see the components in image

	SDL_Surface *tmp = SDL_CreateRGBSurface(SDL_HWSURFACE, img -> w, img -> h, 32, 255, 255, 255, 0);

	Uint32 pixel;
	Uint8 r, g, b;

	struct Component *components = malloc(1000 * sizeof(struct Component)); // array of components : TODO : find a way to get adjustable size

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
					
		                        //bounding box
					if (((float)(c -> width) / ((float) c -> height)) < 1) // aspect ratio
					{
						components[a] = *c;

						DrawRectangle(img_copy, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);

						c -> id = a;
						for (int x = 0; x < (int) c -> points -> size; x += 2)
						{
							Uint8 whitePixel = SDL_MapRGB(img -> format, 255, 255, 255);
							put_pixel(tmp, *(c -> points -> data + x), *(c -> points -> data + x + 1), whitePixel);
						}

						// save components in folder
					
						/*
						char name[10];
						sprintf(name, "%i", a);
						char *res_path;
						int size = asprintf(&res_path,"%s%s%s", "components/", name, ".bmp");
						if (size == -1)
							errx(1, "asprintf()");
						SaveComponentToBMP(img_copy_2, c, res_path);
						*/
						a++;
					}
				}
			}
		}
	}

	SDL_SaveBMP(tmp, "components.bmp");
	SDL_SaveBMP(img_copy, "res.bmp");
	SDL_FreeSurface(img_copy);
	SDL_FreeSurface(tmp);
	SDL_FreeSurface(img_copy_2);

	*len = a;

	return components;

}

void free_component(struct Component *c)
{
	vector_free(c -> points);
	free(c);
}
