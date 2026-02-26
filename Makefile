# Makefile for SDL2 Enigme project

# Compiler
CC = gcc

# Source files
SRC_DIR = src
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/assets.c $(SRC_DIR)/button.c \
       $(SRC_DIR)/events.c $(SRC_DIR)/render.c $(SRC_DIR)/utils.c

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    OUTPUT = enigme.exe
    CFLAGS = -Wall -Wextra -O2 -IC:/msys64/mingw64/include/SDL2
    LDFLAGS = -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image
else
    OUTPUT = enigme
    CFLAGS = -Wall -Wextra -O2 $(shell sdl2-config --cflags)
    LDFLAGS = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_mixer -lSDL2_image
endif

# Default target
all: $(OUTPUT)

# Build executable
$(OUTPUT): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(OUTPUT)

# Clean build artifacts
clean:
	rm -f $(OUTPUT)

# Run the program
run: $(OUTPUT)
	./$(OUTPUT)

.PHONY: all clean run
