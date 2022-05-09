CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0 sdl` -MMD
CFLAGS= `pkg-config --cflags gtk+-3.0 `-Wall -Wextra -Werror  -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl gtk+-3.0 SDL_image` -lm  

SRC =  ui.c ../image_processing/PreProcessing.c ../image_processing/SdlHelperFunctions.c ../image_processing/Sobel.c ../image_processing/Blur.c ../image_processing/Rescaling.c ../image_processing/Hough.c ../image_processing/Drawing.c ../image_processing/Morph.c ../image_processing/Component.c ../image_processing/Video.c ../image_processing/PlateFromImage.c ../image_processing/Vector.c

OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)

ui :  ui.o  ../image_processing/PreProcessing.c ../image_processing/SdlHelperFunctions.c ../image_processing/Sobel.c ../image_processing/Blur.c ../image_processing/Rescaling.c ../image_processing/Hough.c ../image_processing/Drawing.c ../image_processing/Morph.c ../image_processing/Component.c ../image_processing/Video.c ../image_processing/PlateFromImage.c ../image_processing/Vector.c


clean :
	rm *.o *.d ui
