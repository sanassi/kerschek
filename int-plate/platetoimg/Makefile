# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

all: display

display: display.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} display

# END
