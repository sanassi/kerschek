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

#include "Video.h"
#include "PlateFromImage.h"

#include <limits.h>

/*
// use mplayer to play video
void PlayVid(char *path)
{
	int pid = fork();
        fflush(stdout);
        if (pid == 0)
        {
		execlp("mplayer", "mplayer", "-vfm", "ffmpeg", path, (char *) NULL);
                exit(0);
        }
        else if (pid > 0)
        {
		wait(NULL);
        }
}
*/

int main(int argc, char *argv[])
{
	if (argc  > 3)
                return 1;
	
	ReadVideo(argv[1]);

	if (argc == 3 && !strcmp(argv[2], "-p"))
		PlayVid("output.mp4");

	return 0;
}

