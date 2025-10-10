# Project
PROJECT := SDL_fire

# Dirs
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
EXAMPLE_DIR := example
INC_DIR := include
SRC_DIR := src
LIB_INSTALL_DIR := /usr/local/lib
INC_INSTALL_DIR := /usr/local/include

# Files
SRC := $(wildcard $(SRC_DIR)/*.c)
INC := $(INC_DIR)/$(PROJECT).h
LIB_A := $(BUILD_DIR)/lib$(PROJECT).a
LIB_SO := $(BUILD_DIR)/lib$(PROJECT).so
EXAMPLE_MAIN := $(EXAMPLE_DIR)/example.c
EXAMPLE_EXE := $(BUILD_DIR)/example
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
.PHONY: all example install clean

all: CC := gcc
all: CFLAGS := -O3 -march=native -flto
all: CPPFLAGS := -Iinclude
all: $(LIB_A) $(LIB_SO)

example: CC := clang
example: CFLAGS := -Wall -Wextra -Werror -Wunused-result -Wconversion
example: LDFLAGS := -L/usr/local/lib -lSDL_fire -lSDL2
example: $(EXAMPLE_EXE)

install:
	cp $(LIB_A) $(LIB_INSTALL_DIR)
	cp $(LIB_SO) $(LIB_INSTALL_DIR)
	cp $(INC) $(INC_INSTALL_DIR)
	ldconfig

clean:
	rm -rf $(BUILD_DIR)

$(LIB_A): $(OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(LIB_SO): $(OBJ) | $(BUILD_DIR)
	$(CC) -shared -fPIC $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) | $(OBJ_DIR)
	$(CC) -c -fPIC $(CFLAGS) $(CPPFLAGS) $< -o $@

$(EXAMPLE_EXE): $(EXAMPLE_MAIN) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $@
	
$(OBJ_DIR):
	mkdir -p $@
