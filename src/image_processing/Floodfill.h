#ifndef FLOODFILL_H_
#define FLOODFILL_H_

#include <stdio.h>
#include <stdlib.h>

#include "Vector.h"
#include <SDL/SDL.h>
#include "SdlHelper/SdlHelperFunctions.h"

void FloodFill(SDL_Surface *img, int x, int y, int *area);

#endif
