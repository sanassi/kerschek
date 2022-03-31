CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= `pkg-config --cflags glib-2.0 `-Wall -Wextra -Werror  -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image glib-2.0` -lm  

SRC =  Tests.c PreProcessing.c SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Hough.c Drawing.c Morph.c Component.c Video.c PlateFromImage.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

Tests :  Tests.o PreProcessing.c SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Floodfill.c Vector.c Hough.c Drawing.c Morph.c Component.c ArrayConversion.c Video.c PlateFromImage.c


TestVector : TestVector.o Vector.c

TestMorph : TestMorph.o PreProcessing.c SdlHelperFunctions.c Sobel.c Blur.c Rescaling.c Floodfill.c Vector.c Hough.c Drawing.c Morph.c Component.c ArrayConversion.c

clean :
	rm *.o *.d Tests TestVector TestMorph
