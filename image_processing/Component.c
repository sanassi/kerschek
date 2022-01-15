#include "Component.h"

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


void free_component(struct Component *c)
{
	vector_free(c -> points);
	free(c);
}
