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
#include "PlateFromImage.h"


int main()
{
//	init_sdl();

//	SDL_SaveBMP(FrameDifference(load_image("frame_1.png"), load_image("frame_2.png")), "sub.bmp");

//	int h, w;
//	GetVideoResolution("IMG_9234.mp4", &h, &w);

//	printf("\nheight = %i\nwidth = %i\n", h, w);
	ReadVideo();



//	printf("\n%s\n", Input_CMD("IMG_9234.mp4"));

//	printf("\n%s\n", Output_CMD("IMG_9234.mp4", "output.mp4"));
	//printf("heheheh");

//	SDL_Surface *img = SDL_CreateRGBSurface(SDL_HWSURFACE, 500, 500, 32, 0, 0, 0, 0);

//	DrawFillCircle(img, 300, 250, 50, SDL_MapRGB(img -> format, 0, 255, 0));

//	SDL_SaveBMP(img, "cercle.bmp");
	
	return 0;
}
