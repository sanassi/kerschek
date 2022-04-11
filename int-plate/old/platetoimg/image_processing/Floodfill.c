#include "Floodfill.h"

// iterative implem of flood fill algo (similar to graph bfs traversal)
void FloodFill(SDL_Surface *img, int x, int y, int *area)
{
	Uint32 pixel;
	Uint32 redPixel = SDL_MapRGB(img -> format, 255, 0, 0);
	Uint8 r, g, b;

	struct vector *q = vector_new();

	// correction :vector used as a stack here
	vector_push(q, x);
	vector_push(q, y);

	put_pixel(img, x, y, redPixel);
	*area += 1;

	while (vector_isEmpty(q) == 0)
	{
		vector_pop(q, &y);
		vector_pop(q, &x);
		*area += 1;

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

}
