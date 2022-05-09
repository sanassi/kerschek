#ifndef PLATE_FROM_IMAGE_
#define PLATE_FROM_IMAGE_

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

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

char *GetPlateFromImage(char *path, int angle);

int PlateIsOk(char *s);

SDL_Surface *BuildImageRes(char *plate);
#endif
