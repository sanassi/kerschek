#include <stdio.h>
#include <stdlib.h>
#include "Video.h"

void ReadVideo()
{
	//
// Video processing example using FFmpeg
// Written by Ted Burke - last updated 12-2-2017
//

#include <stdio.h>

// Video resolution
#define W 1280
#define H 720

// Allocate a buffer to store one frame
unsigned char frame[H][W][3] = {0};

    int x, y, count;
    int nbRead = 0;

    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    FILE *pipein = popen("ffmpeg -i vid_sample.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 output.mp4", "w");

    // Process video frames
    while(1)
    {
        // Read a frame from the input pipe into the buffer
        count = fread(frame, 1, H*W*3, pipein);

	// Test : save 5th frame to bmp using sdl
	if (nbRead == 5)
	{
		Uint32 pixel;
		Uint8 r, g, b;
		SDL_Surface *img = SDL_CreateRGBSurface(SDL_HWSURFACE, W, H, 32, 0, 0, 0, 0);;


		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				r = (Uint8) frame[i][j][0];
	                        g = (Uint8) frame[i][j][1];
        	                b = (Uint8) frame[i][j][2];
				pixel = SDL_MapRGB(img -> format, r, g, b);
				put_pixel(img, j, i, pixel);
			}
		}

		SDL_SaveBMP(img, "frame.bmp");
	}
	//

        // If we didn't get a frame of video, we're probably at the end
        if (count != H*W*3) break;

        // Process this frame
        for (y=0 ; y<H ; ++y) for (x=0 ; x<W ; ++x)
        {
        	unsigned char val = 0.3 * frame[y][x][0] + 0.6 * frame[y][x][1] + 0.1 * frame[y][x][2];
            // Invert each colour component in every pixel
            frame[y][x][0] = val;
            frame[y][x][1] = val;
            frame[y][x][2] = val;
        }

        // Write this frame to the output pipe
        fwrite(frame, 1, H*W*3, pipeout);

	nbRead++;
    }

    // Flush and close input and output pipes
    fflush(pipein);
    pclose(pipein);
    fflush(pipeout);
    pclose(pipeout);
}
