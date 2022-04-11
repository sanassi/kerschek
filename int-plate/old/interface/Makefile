#SDL mini Makefile

CC=gcc

CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= `pkg-config --cflags gtk+-3.0` -Wall -g -Wextra -Werror -std=c99 -w -O3
CCFLAGS=$(OPT) $(PTHREAD) -pipe
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic  
LDLIBS= `pkg-config --libs gtk+-3.0` `pkg-config --libs sdl` -lSDL_image -lm

all: interface
main: interface.o

clean:
	${RM} *.o
	${RM} *.d
	${RM} interface


# END
