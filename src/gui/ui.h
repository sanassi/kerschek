#ifndef UI_H_
#define UI_H_

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "../image_processing/SdlHelperFunctions.h"
#include "../image_processing/Rescaling.h"
#include "../image_processing/PlateFromImage.h"
#include "../image_processing/Video.h"
int LaunchInterface();

#endif
