#include "PlateFromImage.h"

void MakeDir(char *dirName)
{
        struct stat st = {0};

        if (stat(dirName, &st) == -1)
        {
                mkdir(dirName, 0700);
        }
}


// TODO : clean up
char *GetPlateFromImage(char *path, PlateDetectionArgs *args)
{
	init_sdl();
	SDL_Surface *img = load_image(path);
	SDL_Surface *res = load_image(path);

	int angle = args -> angle;

	int max_h = args -> max_h, min_h = args -> min_h;
        int max_w = args -> max_w, min_w = args -> min_w;
        int min_size = args -> min_size;
        float max_ratio = args -> max_ratio, min_ratio = args -> min_ratio;


        PreProcess(img, 3, 0, 0);

        /*
         * struct Component *GetComponents(SDL_Surface *img,
                int *len, int max_h, int max_w,
                int min_h, int min_w, int min_size,
                float max_ratio, float min_ratio)
         */


	int len;
	struct Component *components = GetComponents(img, 
			&len, max_h, 
			max_w, min_h, 
			min_w, min_size, 
			max_ratio, min_ratio);

	if (!components)
                errx(1, "error : components NULL");


	/*assign id to each component*/
	for (int i = 0; i < len; i++)
	{
		components[i].id = i;
	}

	/*cluster : vector of "colinear" components (vector of ids, so sort faster)*/

	// ok values 1 2 3
	struct vector *current_cluster = GetColinearComponents(components, &len, angle);
	SortComponentVector(current_cluster, 
			components, 
			current_cluster -> size);

	Uint8 color = SDL_MapRGB(res -> format, 255, 0, 0);
	
	struct Component *c;

	/*create folder to store components in*/
	MakeDir("components");
	
	/*extract the components on copy of img (not processed)*/
	//PreProcess(img_copy, 3, 0, 0);


	for (int i = 0; i < (int) current_cluster -> size; i++)
	{
		c = &components[*(current_cluster -> data + i)]; // get component from id
		/*
		DrawRectangle(res, 
				c -> box_origin_y, 
				c -> box_origin_x, 
				c -> height, 
				c ->  width, 
				10, color);
		*/

		/*build filename to save bitmap*/
		char name[3];
                sprintf(name, "%hu", (short) i);
                char *res_path;
                int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");
		if (size == -1)
			printf("error : asprintf()");
		/*-----------------------------------------*/

		SaveComponentToBMP_2(c, res_path, 100);

		/* use gocr to detect characters */
		// why fork() ? execlp stops the current process
		int pid = fork();
		fflush(stdout);
		if (pid == 0)
		{
			execlp("gocr", "gocr", "-o", name, res_path, (char *) NULL);
			exit(0);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		/*----------------------------------------*/
	}

	/*draw the plate bounding box
	 * TODO : clean the code :\
	 * */

	int plate_pos_x = components[*(current_cluster -> data)].box_origin_x;
	int width = components[*(current_cluster -> data + current_cluster -> size - 1)].box_origin_x + 
		components[*(current_cluster -> data + current_cluster -> size - 1)].width
		- plate_pos_x;

	int plate_pos_y;
	int height;

	if (components[*(current_cluster -> data + 0)].box_origin_y 
			< components[*(current_cluster -> data + current_cluster -> size - 1)].box_origin_y)
	{
		plate_pos_y = components[*(current_cluster -> data + 0)].box_origin_y;
		height = components[*(current_cluster -> data + current_cluster -> size - 1)].box_origin_y 
			+ components[*(current_cluster -> data + current_cluster -> size - 1)].height
			- components[*(current_cluster -> data + 0)].box_origin_y;
	}
	else
	{
		plate_pos_y = components[*(current_cluster -> data + current_cluster -> size - 1)].box_origin_y;
		height = components[*(current_cluster -> data + 0)].box_origin_y 
			+ components[*(current_cluster -> data + 0)].height
			- components[*(current_cluster -> data + current_cluster -> size - 1)].box_origin_y;
	}

	
	DrawRectangle(res,
                                plate_pos_y,
                                plate_pos_x,
                                height,
                                width,
                                10, color);

	SDL_Surface *plate_img = SDL_CreateRGBSurface(SDL_HWSURFACE, width, height, 32, 0, 0, 0, 0); 
	SDL_Surface *img_copy = load_image(path);

	for (int i = plate_pos_x; i < res -> w && i < plate_pos_x + width; i++)
	{
		for (int j = plate_pos_y; j < res -> h && j < plate_pos_y + height; j++)
		{
			put_pixel(plate_img, i - plate_pos_x, j - plate_pos_y, get_pixel(img, i, j));
		}
	}

	SDL_SaveBMP(plate_img, "plate_img.bmp");
	SDL_FreeSurface(plate_img);
	SDL_FreeSurface(img_copy);


	/*------------------------------------------------------*/


	SDL_SaveBMP(res, "final.bmp");

	/*-----------Reconstruction de la plaque----------------*/

	/*read digits*/
	char *plate = malloc(7 * sizeof(char));
	char number[2];

	for (int i = 0; i < 7; i++)
	{
		// convert number to string
		sprintf(number, "%hu", (short) i);

		FILE *fp = fopen(number, "r");
		plate[i] = toupper(fgetc(fp)); // toupper() : so all char are uppercase
        	fclose(fp);
	}


	/*free*/
	SDL_FreeSurface(img);
	SDL_FreeSurface(res);

	vector_free(current_cluster);

	free(components);

	return plate;
}


int PlateIsOk(char *s)
{
	// return val : 1 FALSE
	// 		0 TRUE
	
	for (int i = 0; i < 7; i++)
	{
		// ocr didn't work
		if (s[i] == '_')
			return 1;
		// character is not alphanumeric
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')))
			return 1;

		// character is not a plate character
		if (s[i] == 'I' || s[i] == 'U' || s[i] == 'O')
			return 1;
	}

	return 0;
}

SDL_Surface *BuildImageRes(char *plate)
{
	int digitHeight = 200;
	int digitWidth = 100;

	int offset_h = 20;
	int offset_w = 70;

	SDL_Surface *res = SDL_CreateRGBSurface(SDL_HWSURFACE, 
			7 * digitWidth + 3 * offset_w, 
			150, 32, 0, 0, 0, 0);

	Uint32 whitePix = SDL_MapRGB(res -> format, 255, 255, 255);

	for (int i = 0; i < res -> w; i++)
	{
		for (int j = 0; j < res -> h; j++)
		{
			put_pixel(res, i, j, whitePix);
		}
	}

	int pos_x = offset_w;
	int pos_y = offset_h;

	for (int i = 0; i < 7; i++)
	{
		char *digitPath;

		if (plate[i] == '_' || isalnum(plate[i]) == 0)
		{
			digitPath = "digits_to_print/under.bmp";
		}

		else
		{
			int size = asprintf(&digitPath, "%s%c%s", "digits_to_print/", plate[i], ".bmp");
                	printf("%s\n", digitPath);
                	if (size == -1)
                        	printf("error : asprintf()");
		}

		SDL_Surface *digit = ResizeToFit(load_image(digitPath), digitWidth, digitHeight);

		for (int j = 0; j < digit -> w; j++)
		{
			for (int k = 0; k < digit -> h; k++)
			{
				put_pixel(res, j + pos_x, k + pos_y, get_pixel(digit, j, k));
			}
		}

		pos_x += digit -> w + offset_w;

	}

	return ResizeToFit(res, 5 * digitWidth, digitHeight);

}
