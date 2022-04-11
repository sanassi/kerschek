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
char *GetPlateFromImage(char *path, int angle)
{
	init_sdl();
	SDL_Surface *img = load_image(path);
	//SDL_Surface *img_copy = load_image(path);
	SDL_Surface *res = load_image(path);


	int max_h = img -> h / 2, min_h = 30;
        int max_w = img -> w / 3, min_w = 10;
        int min_size = 10;
        float max_ratio = 1, min_ratio = 0.2;


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
	SortComponentVector(current_cluster, components, current_cluster -> size);

	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);
	
	struct Component *c;

	/*create folder to store components in*/
	MakeDir("components");
	
	/*extract the components on copy of img (not processed)*/
	//PreProcess(img_copy, 3, 0, 0);
	for (int i = 0; i < (int) current_cluster -> size; i++)
	{
		c = &components[*(current_cluster -> data + i)]; // get component from id
		DrawRectangle(res, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 10, color);

		/*build filename to save bitmap*/
		char name[3];
                sprintf(name, "%hu", (short) i);
                char *res_path;
                int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");
		if (size == -1)
			printf("error : asprintf()");
		/*-----------------------------------------*/

		SaveComponentToBMP_2(c, res_path, 100);

		/* use gocr to recog characters */
		// why fork() ? execlp stops the current process
		int pid = fork();
		fflush(stdout);
		if (pid == 0)
		{
			execlp("gocr", "gocr", "-o",name, res_path, (char *) NULL);
			exit(0);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		/*----------------------------------------*/
	}

	SDL_SaveBMP(res, "final.bmp");

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
	//SDL_FreeSurface(img_copy);
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
