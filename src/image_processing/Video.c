#include "Video.h"
#include <limits.h>
#include <sys/wait.h>


void GetVideoResolution(char *vid_path, int *height, int *width)
{
	int BUF_SIZE = 10;

	// use pipe to get resolutoin from stdout and store in string
	// ffpropbe displays result in stdout
	char res[BUF_SIZE];
	int stdout_bk = 0;
	int pipefd[2];
	int e = pipe(pipefd);
	if (e == -1)
		printf("err");

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

/*
 * ReadVideo() : open video and read frame through a pipe
 *
 * get video resolution with ffprobe
 *
 * save first frame
 * for each frame : 
 * 	1 - save previous frame
 * 	2 - grayscale
 *	3 - compute differece frame between current and prev
 *	4 - extract components on difference image (motion change)
 *	5 - draw bouding box around components
 *	6 - 
 *
 * */

void ReadVideo(char *vid_path)
{
	// Get Video Resolution
	int H = 1, W = 1;
	GetVideoResolution(vid_path, &H, &W);

	printf("\n%i  %i\n", H, W);

	// Allocate a buffer to store one frame
	unsigned char frame[H][W][3];

    	int x, y, count;
    	int nbRead = 1;

	/*
	*/

    	Uint32 pixel;
    	Uint8 r, g, b;
	SDL_Surface *prev;

	// Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg

	FILE *pipein = popen(Input_CMD(vid_path), "r");
        FILE *pipeout = popen(Output_CMD(vid_path, "output.mp4"), "w");


    	// use the first frame as background image
	for (int i = 0; i < 1; i++)
		count = fread(frame, 1, H*W*3, pipein);
	//fseek(pipein, 0, SEEK_SET);

	if (count == -1)
		printf("err");
    	SDL_Surface *background = SDL_CreateRGBSurface(SDL_HWSURFACE, W, H, 32, 0, 0, 0, 0);
	Uint8 color = SDL_MapRGB(background -> format, 0, 255, 0);

	/*convert frame to sdl_surface (easier to use)*/
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

	Grayscale(background);
    	SDL_SaveBMP(background, "back.bmp");
	prev = copy_image(background);
	int saved = 0;

    	// Process video frames
    	while(1)
    	{
		// Read a frame from the input pipe into the buffer
		count = fread(frame, 1, H*W*3, pipein);
		nbRead++;

		/*read 1 frame skip 5*/
		if (nbRead % 5 != 0)
			continue;

		// If we didn't get a frame of video, we're probably at the end
		if (count != H * W * 3) 
			break;

		// Process this frame

		SDL_Surface *img = SDL_CreateRGBSurface(SDL_HWSURFACE, W, H, 32, 0, 0, 0, 0);
		Grayscale(img);


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

		/* copy original frame to write in output pipe*/
		SDL_Surface *frame_copy = copy_image(img);
		
		/* image differencing */
		SDL_Surface *sub = FrameDifference(prev, img);

		/*extract large components*/
		int len;
		struct Component *components = GetComponents(sub, 
				&len, 
				INT_MAX, 
				INT_MAX, 
				30, 
				30, 
				85, 
				DBL_MAX, 
				1);


		/*loop through component array and check if overlap
		 *if overlap : merge components and remove them
		 then append merge to end of component array
		 * */

		// append merged component to the end of
		// component array
		// TODO : fix :/
		//int l = len;
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
			{
				if (i == j)
					continue;

				if (Overlap(&components[i], &components[j]) == 1)
        			{
                			struct Component *merge = MergeComponents(&components[i], 
							&components[j]);

					//if (l < MAX_LEN)
					{
                				components[i] = *merge;
                				components[j].id = -1;
                				//components[l] = *merge;
                				//l += 1;
					}
        			}
			}
		}

		// pb
		//len = l;

		/*draw bounding boxes around components and save only one near the center
		 *boxes drawn in output
		 * */
		for (int i = 0; i < len; i++)
		{
			struct Component *c = &components[i]; // get component from id
                
			// check if component was previouly mreged
			// yes : skip the component	
			if (c -> id == -1)
                                continue;

			DrawRectangle(frame_copy, 
					c -> box_origin_y, 
					c -> box_origin_x, 
					c -> height,
					c ->  width, 
					4, 
					SDL_MapRGB(frame_copy -> format, 0, 255, 0));

			/*save first component that reaches center of image*/
			if (nbRead % 10 == 0 && saved < 20 && 
					c -> points -> size > 200 && 
					abs((c -> box_origin_x + c -> width / 2) - W / 2) < 300)
			{
				saved += 1;
				char *res_path;
				asprintf(&res_path, "%s%i%s", "frames/", saved, ".bmp");
				SDL_SaveBMP(img, res_path);
			}
		}


		/* write difference frame to output */
		/*ie convect surface to frame*/
		for (y=0 ; y<H; y++) for (x=0 ; x<W; x++)
		{
			pixel = get_pixel(frame_copy, x, y);
			SDL_GetRGB(pixel , frame_copy -> format, &r, &g, &b);
			frame[y][x][0] = (unsigned char) r;
		    	frame[y][x][1] = (unsigned char) g;
			frame[y][x][2] = (unsigned char) b;
		}

		/*write frame to output pipe*/
		count = fwrite(frame, 1, H*W*3, pipeout);

		/*free difference image*/
		SDL_FreeSurface(sub);

		/*save previous frame*/
		prev = copy_image(img);

		/*make sure that we wrote all pixels to output*/
		if (count != H * W * 3)
			break;
    	}

	// Flush and close input and output pipes
	fflush(pipein);
	pclose(pipein);
	fflush(pipeout);
	pclose(pipeout);

	SDL_FreeSurface(prev);
	SDL_FreeSurface(background);
}


/*compute squared distance between points in 3 dimensional space (here : color space)*/
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

        Uint32 res_pixel = SDL_MapRGB(img_1 -> format, 0, 0, 0);

	/*channels for each image*/
        Uint8 r_1, g_1, b_1;
        Uint8 r_2, g_2, b_2;

        int threshold = 70;

        for (int i = 0; i < img_1 -> w; i++)
        {
                for (int j = 0; j < img_1 -> h; j++)
                {
                        pixel_1 = get_pixel(img_1, i, j);
                        pixel_2 = get_pixel(img_2, i, j);

                        SDL_GetRGB(pixel_1, img_1 -> format, &r_1, &g_1, &b_1);
                        SDL_GetRGB(pixel_2, img_2 -> format, &r_2, &g_2, &b_2);

			/*compute squared distance between colors*/
                        int d_Sq = distSq(r_1, b_1, g_1, r_2, g_2, b_2);

			
                        if (d_Sq > threshold * threshold)
                        {
                                put_pixel(sub, i, j, res_pixel);
                        }
			else
			{
				/* no important color change, so put white pixel */
				put_pixel(sub, i, j, SDL_MapRGB(img_1 -> format, 255, 255, 255));
			}
                }
        }

        return sub;
}
