#ifndef PLATE_FROM_IMAGE_H_
#define PLATE_FROM_IMAGE_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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
//#include "Video.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct PlateDetectionArgs
{
        int angle;
        int max_h, max_w;
        int min_h, min_w;
        int min_size;
        float max_ratio, min_ratio;

}PlateDetectionArgs;

char *GetPlateFromImage(char *path, PlateDetectionArgs *args);

int PlateIsOk(char *s);

SDL_Surface *BuildImageRes(char *plate);

/*
         * struct Component *GetComponents(SDL_Surface *img,
                int *len, int max_h, int max_w,
                int min_h, int min_w, int min_size,
                float max_ratio, float min_ratio)
         */

void MakeDir(char *dirName);
#endif
