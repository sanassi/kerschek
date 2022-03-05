#include "PlateFromImage.h"

// TODO : clean up
char *GetPlateFromImage(char *path, int angle)
{
	init_sdl();
	SDL_Surface *img = load_image(path);
	SDL_Surface *img_copy = load_image(path);
	SDL_Surface *res = load_image(path);

	PreProcess(img, 3, 0, 0);
	
	 //struct Component *GetComponents(SDL_Surface *img,
           //     int *len, int max_h, int max_w, int min_h, int min_w, int min_size,
           //     float max_ratio, float min_ratio);
	 

	int len;
	// TODO : use struct component hint  as arg to get components
	struct Component *components = GetComponents(img, &len, img -> h / 2, img -> w / 3, 30, 10, 50, 1, 0);

	if (!components)
                errx(1, "err");

	for (int i = 0; i < len; i++)
	{
		components[i].id = i;
	}

	// cluster : set of "colinear" components

	// ok values
	// angle val 3
	// angle val 1
	// agnle val 2
	struct vector *current_cluster = GetColinearComponents(components, &len, angle);

	SortComponentVector(current_cluster, components, current_cluster -> size);

	Uint8 color = SDL_MapRGB(img -> format, 255, 0, 0);
	struct Component *c;
	
	Binarize(img_copy);
	
	for (int i = 0; i < (int) current_cluster -> size; i++)
	{
		c = &components[*(current_cluster -> data + i)];
		DrawRectangle(res, c -> box_origin_y, c -> box_origin_x, c -> height,c ->  width, 4, color);

		// build path to save bitmap
		char name[3];
                sprintf(name, "%hu", (short) i);
                char *res_path;
                int size = asprintf(&res_path, "%s%s%s", "components/", name, ".bmp");
		//

		if (size == -1)
			printf("error : asprintf()");

		//SaveComponentToBMP(img_copy, c, res_path);
		SaveComponentToBMP_2(c, res_path, 40);

		// use gocr to recog characters
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
		// end gocr
	}

	SDL_SaveBMP(res, "final.bmp");

	// read digits
	//
	
	char *plate = malloc(7 * sizeof(char));
	char number[2];

	for (int i = 0; i < 7; i++)
	{
		sprintf(number, "%hu", (short) i);

		FILE *fp = fopen(number, "r");
		plate[i] = toupper(fgetc(fp)); // so all char are uppercase
        	fclose(fp);
	}
	
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
		// is not alphanumeric
		if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')))
			return 1;

		// is not a plate character
		if (s[i] == 'I' || s[i] == 'U' || s[i] == 'O')
			return 1;
	}

	return 0;
}
