#include "ArrayConversion.h"

double *BW_BitmapToArray(SDL_Surface *img)
{
	double *arr = malloc(img -> h * img -> w * sizeof(double));

	Uint32 pixel;
	Uint8 r, g, b;

	for (int i = 0; i < img -> h; i++)
	{
		for (int j = 0; j < img -> w; j++)
		{
			pixel = get_pixel(img, j, i);

			SDL_GetRGB(pixel, img -> format, &r, &g, &b);

			if ((r == 0) && (g == 0) & (b == 0))
			{
				arr[i * img -> w + j] = 1;
			}
			else
			{
				arr[i * img -> w + j] = 0; 
			}

			printf("%i ",(int) arr[i * img -> w + j]);
		}

		printf("\n");
	}

	return arr;
}
