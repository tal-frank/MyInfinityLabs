
#-----------------------------------------------------------------#
########################### DIRECTORIES ###########################
#-----------------------------------------------------------------#

NAME ?= foo
C_DIR = $(HOME)/git/c
DS_DIR = $(HOME)/git/ds
SRC_DIR = $(DS_DIR)/src
INC_DIR = $(DS_DIR)/include
TEST_DIR = $(DS_DIR)/test
BIN_DIR = $(DS_DIR)/bin
DEBUG_DIR = $(BIN_DIR)/debug
RELEASE_DIR = $(BIN_DIR)/release
ODIR = $(SRC_DIR)/objects

#--------------------------------------------------------------------#
########################### COMPILER FLAGS ###########################
#--------------------------------------------------------------------#

CC = gcc
FLAGS = -ansi -pedantic-errors -Wall -Wextra -I$(INC_DIR)
GD = $(FLAGS) -g
GC = $(FLAGS) -DNDEBUG -O3
VLG_FLAGS = --leak-check=yes --track-origins=yes

#----------------------------------------------------------------------------#
########################### FILE NAMES & LOCATIONS ###########################
#----------------------------------------------------------------------------#

SRC = $(SRC_DIR)/$(NAME).c 

TEST = $(TEST_DIR)/$(NAME)_test.c

_OBJ = $(NAME).o $(NAME)_test.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

DEBUG_TARGET = $(DEBUG_DIR)/$(NAME)_debug.out
RELEASE_TARGET = $(RELEASE_DIR)/$(NAME)_release.out

#-----------------------------------------------------------#
########################### RULES ###########################
#-----------------------------------------------------------#

all: run clean

run: debug
	@$(DEBUG_TARGET)

run_r: release
	@$(RELEASE_TARGET)

$(NAME).o: $(TEST) $(SRC)
	@$(CC) $(GD) -c $^
	@echo "created object files"
	
obj: $(NAME).o
	
debug: $(TEST) $(SRC)
	@$(CC) $(GD) $(TEST) $(SRC) -o $(DEBUG_TARGET)
	@echo "finished debug compilation"

release: $(TEST) $(SRC)
	@$(CC) $(GC) $(TEST) $(SRC) -o $(RELEASE_TARGET)
	@echo "finished release compilation"
vlg: debug
	@valgrind $(VLG_FLAGS) $(DEBUG_TARGET)

PHONY: vlg, debug, clean, run, obj
	
clean:
	@-rm $(SRC_DIR)/$(NAME).o $(RELEASE_DIR)/$(NAME)_release.out $(DEBUG_DIR)/$(NAME)_debug.out







