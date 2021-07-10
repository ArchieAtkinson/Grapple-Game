# A simple Makefile for compiling small SDL projects

# set the compiler
CC := gcc
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/game
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#set the preprocessor flags
CPPFLAGS := -Iinclude

# set the compiler flags
CFLAGS := `pkg-config raylib --cflags`
CFLAGS += -ggdb3
CFLAGS += -O0
CFLAGS += --std=c11
CFLAGS += -Wall
CFLAGS += -Werror
CFLAGS += -Wextra


# set the linkers flags
LDFLAGS :=

# link in libaries
LDLIBS := `pkg-config raylib --libs`
LDLIBS += -lm

.PHONY: all clean

all: $(EXE)
	./bin/game 

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
.PHONY: all clean
