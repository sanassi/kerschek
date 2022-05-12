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
#include <sys/types.h>
#include <sys/stat.h>

//#include "Video.h"
#include "PlateFromImage.h"

#include <limits.h>

struct Array
{
	int x, y, w;
	unsigned char *data;
};

void SetValue(struct Array *arr, int i, int j, int k, unsigned char val)
{
	arr -> data[arr -> w * (arr -> x * i + j) + k] = val;
}

unsigned char GetValue(struct Array *arr, int i, int j, int k)
{
        return arr -> data[arr -> w * (arr -> x * i + j) + k];
}

/*
 *goal : use array as buffer to reda frames more efficiently
 * */
/*
int main()
{
	struct Array *arr = malloc(sizeof(struct Array));
	arr -> x = 5;
	arr -> y = 5;
	arr -> w = 2;

	arr -> data = malloc((arr -> x * arr -> y * arr -> w) * sizeof(double));

	int cpt = 0;

	for (int i = 0; i < arr -> x; i++)
	{
		for (int j = 0; j < arr -> y; j++)
		{
			printf("[");
			for (int k = 0; k < arr -> w; k++)
			{
				//arr -> data[arr -> w * (arr -> x * i + j) + k] = cpt;

				SetValue(arr, i, j, k, cpt);
				printf(" %f ", arr -> data[arr -> w * (arr -> x * i + j) + k]);
			}
			printf("] ");
		}
		cpt++;
		printf("\n");
	}

	//
	// Video processing example using FFmpeg
	// Written by Ted Burke - last updated 12-2-2017
	//	

	int H = 336;
	int W = 596;

	struct Array *arr = malloc(sizeof(struct Array));
        arr -> x = H;
        arr -> y = W;
        arr -> w = 3;

        arr -> data = malloc((arr -> x * arr -> y * arr -> w) * sizeof(unsigned char));

	struct Array *arr2 = malloc(sizeof(struct Array));
        arr2 -> x = H;
        arr2 -> y = W;
        arr2 -> w = 3;

        arr2 -> data = malloc((arr2 -> x * arr2 -> y * arr2 -> w) * sizeof(unsigned char));
	// Allocate a buffer to store one frame
	//unsigned char frame[H][W][3] = {0};

    	int x, y, count;

    	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    	FILE *pipein = popen("ffmpeg -i videos/cars2.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    	FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 596x336 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 output.mp4", "w");

    	// Process video frames
    	while(1)
    	{
        	// Read a frame from the input pipe into the buffer
        	count = fread(arr -> data, 1, H*W*3, pipein);

        	// If we didn't get a frame of video, we're probably at the end
        	if (count != H*W*3) break;

        	// Process this frame
        	for (y=0 ; y<H ; y++) for (x=0 ; x<W ; x++)
        	{
			unsigned char r = GetValue(arr, y, x, 0);
			unsigned char g = GetValue(arr, y, x, 1);
			unsigned char b = GetValue(arr, y, x, 2);

			//double val = 0.3 * r + 0.6 * g + 0.1 * b;
            		// Invert each colour component in every pixel
            		SetValue(arr2, y, x, 0, (unsigned char) r); // red
            		SetValue(arr2, y, x, 1, (unsigned char) g); // green
            		SetValue(arr2, y, x, 2, (unsigned char) b);; // blue
        	}

        	// Write this frame to the output pipe
        	fwrite(arr2 -> data, 1, H*W*3, pipeout);
    	}

    	// Flush and close input and output pipes
    	fflush(pipein);
    	pclose(pipein);
    	fflush(pipeout);
    	pclose(pipeout);
	return EXIT_SUCCESS;
}
*/
