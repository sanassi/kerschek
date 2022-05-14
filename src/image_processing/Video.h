#ifndef VIDEO_H_
#define VIDEO_H_

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include "SdlHelperFunctions.h"
#include <unistd.h>
#include <string.h>
#include "Drawing.h"
#include "Component.h"

#include "PlateFromImage.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


// use mplayer to display videos
void PlayVid(char *path);

void ReadVideo(char *vid_path);

int GetNbFrames(char *vid_path);

int distSq(int x1, int y1, int z1, int x2, int y2, int z2);

SDL_Surface *FrameDifference(SDL_Surface *img_1, SDL_Surface *img_2);

void GetVideoResolution(char *vid_path, int *height, int *width);

char *Input_CMD(char *vid_path);

char *Output_CMD(char *vid_path, char *vid_output_path);

#endif
