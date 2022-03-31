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
#include "Video.h"
#include "PlateFromImage.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
    return 1;
  char *plate = GetPlateFromImage(argv[1], 2);	;

      
  printf("START\n");
  FILE *res;
  char *filename = argv[1];
  strcat(filename, ".tochar");

  res = fopen(filename, "w");
  fprintf(res, "%s", plate);
  fclose(res);


  printf("%s\n",plate);
  printf("END\n");
  return 0;
}

