CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -O3
CPPFLAGS= `pkg-config --cflags sdl` -MMD
LDLIBS= `pkg-config --libs sdl SDL_image` -lm
TARGET = Tests

MAIN = src/image_processing/Tests.o
OBJ = $(patsubst %.c, %.o, $(wildcard src/*/*.c))

HEADERS = $(wildcard src/*/*.h)
INC_FLAGS = $(addprefix -I, $(dir $(wildcard src/*/)))

CFLAGS += $(INC_FLAGS)

all: release

release: CFLAGS += -O2
release: CPPFLAGS += -DNDBUG
release: $(TARGET)

$(TARGET): $(MAIN) $(OBJ)
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(OBJ): %.o: %.c $(HEADERS)

.PHONY: clean

clean:
	$(RM) $(TARGET)
	$(RM) $(MAIN)
	$(RM) $(OBJ)
