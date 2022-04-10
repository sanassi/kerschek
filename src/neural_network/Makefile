# Simple SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl glib-2.0` -MMD
CFLAGS=  -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl glib-2.0` -lSDL_image -lm -ldl

SRC = main.c neural_network.c  tools.c
OBJ = $(SRC:.c=.o)
DEP = $(SRC:.c=.d)


all:  main

main: $(OBJ)

clean:
	${RM} *.o
	${RM} *.d
	${RM} main

# END
