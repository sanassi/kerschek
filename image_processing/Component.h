#ifndef COMPONENT_H_
#define COMPONENT_H_


#include <stdio.h>
#include <stdlib.h>
#include "Sobel.h"
#include "Blur.h"
#include "PreProcessing.h"
#include "SdlHelper/SdlHelperFunctions.h"
#include "Rescaling.h"
#include "Floodfill.h"
#include "Morph.h"
#include "Drawing.h"
#include "Vector.h"
#include "Hough.h"
#include <string.h>

struct Component
{
	int box_origin_x, box_origin_y; // bounding box coordinates

	int height, width;

	int id;


	// extreme points
	int leftmost_x, leftmost_y;
	int rightmost_x, rightmost_y;
	int topmost_x, topmost_y;
	int bottommost_x, bottommost_y;
	
	// pixel points of the component
	struct vector *points; // pixel points of the component
};

struct Component *GetComponent(SDL_Surface *img, int x, int y);

void SaveComponentToBMP(SDL_Surface *img, struct Component *c, char *name);

void free_component(struct Component *c);

struct Component *GetComponents(SDL_Surface *img, int *len);


#endif
