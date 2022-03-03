#ifndef PREPROCESSING_H_
#define PREPROCESSING_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "SdlHelperFunctions.h"

void Grayscale(SDL_Surface *image);

void Binarize(SDL_Surface* image_surface);

void Invert(SDL_Surface *img);
#endif
