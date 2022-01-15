CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image` -lm 

SRC =  Tests.c PreProcessing.c SdlHelper/SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Hough.c Drawing.c Morph.c Component.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

Tests :  Tests.o PreProcessing.c SdlHelper/SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Floodfill.c Vector.c Hough.c Drawing.c Morph.c Component.c

TestVector : TestVector.o Vector.c


clean :
	rm *.o *.d Tests TestVector
