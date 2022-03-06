#include "Video.h"

#include <sys/wait.h>

void GetVideoResolution(char *vid_path, int *height, int *width)
{
	int BUF_SIZE = 10;

	// use pipe to get resolutoin from stdout and store in string
	// ffpropbe displays result in stdout
	char res[BUF_SIZE];
	int stdout_bk;
	int pipefd[2];
	pipe(pipefd);

	dup2(pipefd[1], STDOUT_FILENO);
	fflush(stdout);

	// to get video resolution (WIDTHxHEIGHT)

	// use fork because execlp stops program if 0 errors
	int pid = fork();
	if (pid == 0)
	{
		execlp("ffprobe",
                        "ffprobe",
                        "-v",
                        "error",
                        "-select_streams",
                        "v:0",
                        "-show_entries",
                        "stream=width,height",
                        "-of",
                        "default=nw=1:nk=1",
                        vid_path,
                        (char *) NULL);

		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}

	close(pipefd[1]);
	dup2(stdout_bk, STDOUT_FILENO);


	// save resolution in width and height param
	ssize_t r = read(pipefd[0], res, BUF_SIZE);
	res[r - 1] = '\0'; // in stdout : last char is a new line char so terminate strign before
	
	char *token = strtok(res, "\n");
	*width = (int) strtoul(token, NULL, 10);

	token = strtok(NULL, "\n");
	*height = (int) strtoul(token, NULL, 10);
}

// return string used as arg for popen()
char *Input_CMD(char *vid_path)
{
	char arg_1[] = "ffmpeg -i ";
	char arg_2[] = " -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -";

	//int len = strlen(vid_path) + strlen(arg_2) + strlen(arg_1);
	
	// build command
	char *res;
	int size = asprintf(&res, "%s%s%s", arg_1, vid_path, arg_2);

	if (size == -1)
		errx(EXIT_FAILURE, "error : Input_CMD() : asprintf()");
	return res;
}

char *Output_CMD(char *vid_path, char *vid_output_path)
{
	int h, w;
	GetVideoResolution(vid_path, &h, &w);
	char x[] = "x";

	char *res;

	char arg_1[] = "ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s ";
	char arg_2[] = " -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 ";

	int size = asprintf(&res, "%s%d%s%d%s%s", arg_1, w, x, h, arg_2, vid_output_path);

	if (size == -1)
		errx(EXIT_FAILURE, "error : Output_CMD() : asprintf()");

	return res;
}


void ReadVideo()
{
	// Get Video Resolution
	int H = 1, W = 1;
	GetVideoResolution("IMG_9234.mp4", &H, &W);

	// Allocate a buffer to store one frame
	unsigned char frame[H][W][3];

    	int x, y, count;
    	int nbRead = 0;


    	Uint32 pixel;
    	Uint8 r, g, b;



    	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    	FILE *pipein = popen(Input_CMD("IMG_9234.mp4"), "r");
    	FILE *pipeout = popen(Output_CMD("IMG_9234.mp4", "output.mp4"), "w");


    	// use the first frame as background image
	fread(frame, 1, H*W*3, pipein);
    	SDL_Surface *background = SDL_CreateRGBSurface(SDL_HWSURFACE, W, H, 32, 0, 0, 0, 0);

    	for (int i = 0; i < H; i++)
    	{
    		for (int j = 0; j < W; j++)
		{
			r = (Uint8) frame[i][j][0];
			g = (Uint8) frame[i][j][1];
			b = (Uint8) frame[i][j][2];
			pixel = SDL_MapRGB(background -> format, r, g, b);
			put_pixel(background, j, i, pixel);
		}
    	}
    	SDL_SaveBMP(background, "back.bmp");



    	// Process video frames
    	while(1)
    	{
		// Read a frame from the input pipe into the buffer
		count = fread(frame, 1, H*W*3, pipein);
		// If we didn't get a frame of video, we're probably at the end
		if (count != H*W*3) break;

		// Process this frame

		SDL_Surface *img = SDL_CreateRGBSurface(SDL_HWSURFACE, W, H, 32, 0, 0, 0, 0);;


		// convert frame to sdl_surface
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

		//
		
		SDL_Surface *sub = FrameDifference(img, background);


		// write difference frame to output
		for (y=0 ; y<H; ++y) for (x=0 ; x<W; ++x)
		{
			pixel = get_pixel(sub, x, y);
			SDL_GetRGB(pixel , img -> format, &r, &g, &b);
			frame[y][x][0] = (unsigned char) r;
		    	frame[y][x][1] = (unsigned char) g;
			frame[y][x][2] = (unsigned char) b;
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


int distSq(int x1, int y1, int z1, int x2, int y2, int z2)
{
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);
}

SDL_Surface *FrameDifference(SDL_Surface *img_1, SDL_Surface *img_2)
{
	// image difference
        SDL_Surface *sub = SDL_CreateRGBSurface(SDL_HWSURFACE, img_1 -> w, img_1 -> h, 32, 0, 0, 0, 0);

        Uint32 pixel_1;
        Uint32 pixel_2;

        Uint32 res_pixel = SDL_MapRGB(img_1 -> format, 255, 255, 255);

        Uint8 r_1, g_1, b_1;
        Uint8 r_2, g_2, b_2;

	int x_average = 0, y_average = 0;
	int count = 0;

        int threshold = 80;

        for (int i = 0; i < img_1 -> w; i++)
        {
                for (int j = 0; j < img_1 -> h; j++)
                {
                        pixel_1 = get_pixel(img_1, i, j);
                        pixel_2 = get_pixel(img_2, i, j);

                        SDL_GetRGB(pixel_1, img_1 -> format, &r_1, &g_1, &b_1);
                        SDL_GetRGB(pixel_2, img_2 -> format, &r_2, &g_2, &b_2);

                        int d_Sq = distSq(r_1, b_1, g_1, r_2, g_2, b_2);

                        if (d_Sq > threshold * threshold)
                        {
                                put_pixel(sub, i, j, res_pixel);
				x_average += i;
				y_average += j;
				count += 1;
                        }
			else
			{
				put_pixel(sub, i, j, SDL_MapRGB(img_1 -> format, 0, 0, 0));
			}
                }
        }

	x_average = x_average / count;
	y_average = y_average / count;


	DrawFillCircle(sub, y_average, x_average, 30, SDL_MapRGB(sub -> format, 255, 0, 0));

        return sub;
}
