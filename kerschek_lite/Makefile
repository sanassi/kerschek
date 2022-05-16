CC=gcc

CFLAGS= `pkg-config --cflags glib-2.0`-Wall -Wextra -Werror  -std=c99 -O3 
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image glib-2.0` -lm  

SRC =  TestPlate.c TestVid.c PreProcessing.c SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Hough.c Drawing.c Morph.c Component.c Video.c PlateFromImage.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

KerschekLite :  KerschekLite.o PreProcessing.c SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c  Vector.c  Drawing.c Morph.c Component.c  Video.c PlateFromImage.c





clean :
	rm *.o KerschekLite
