#ifndef VIDEO_H
#define VIDEO_H

#include <stdio.h>
#include <stdlib.h>
#include "SdlHelperFunctions.h"
#include <unistd.h>
#include <string.h>
#include "Drawing.h"

void ReadVideo();

int distSq(int x1, int y1, int z1, int x2, int y2, int z2);

SDL_Surface *FrameDifference(SDL_Surface *img_1, SDL_Surface *img_2);

void GetVideoResolution(char *vid_path, int *height, int *width);

char *Input_CMD(char *vid_path);

char *Output_CMD(char *vid_path, char *vid_output_path);

#endif
