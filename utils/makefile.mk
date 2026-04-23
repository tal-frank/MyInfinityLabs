
#-----------------------------------------------------------------#
########################### DIRECTORIES ###########################
#-----------------------------------------------------------------#

NAME       ?= foo
PROJECT    ?= ds

GIT_DIR     = $(HOME)/git
C_DIR       = $(HOME)/git/c
DS_DIR      = $(HOME)/git/ds
SRC_DIR     = $(DS_DIR)/src
INC_DIR     = $(DS_DIR)/include
TEST_DIR    = $(DS_DIR)/test
BIN_DIR     = $(DS_DIR)/bin
DEBUG_DIR   = $(BIN_DIR)/debug
RELEASE_DIR = $(BIN_DIR)/release
ODIR        = $(SRC_DIR)/objects

null :=
space := $(null) $(null)

#--------------------------------------------------------------------#
########################### COMPILER FLAGS ###########################
#--------------------------------------------------------------------#

CC        = gcc
FLAGS     = -ansi -pedantic-errors -Wall -Wextra $(INCLUDE)  ###-I$(INC_DIR)
GD        = $(FLAGS) -g
GC        = $(FLAGS) -DNDEBUG -O3
VLG_FLAGS = --leak-check=yes --track-origins=yes

#----------------------------------------------------------------------------#
########################### FILE NAMES & LOCATIONS ###########################
#----------------------------------------------------------------------------#


SRC             = $(SRC_DIR)/$(NAME).c
MAIN_SRC        = $(filter %/$(NAME).c, $(ALL_SRC))
ALL_SRC_DIRS    = $(addprefix $(GIT_DIR)/, $(PROJECT)/ $(subset :, ,$(ADDITIONAL_SRC_DIRS)))
ALL_SRC_SUBDIRS = $(sort $(shell find $(ALL_SRC_DIRS) -type d 2>/dev/null))
ALL_SRC         = $(sort $(shell find $(ALL_SRC_SUBDIRS) -name "*.c" 2>/dev/null))

VPATH		= $(subst $(space),:,$(strip $(ALL_SRC_SUBDIRS)))
INCLUDE         = -I$(INC_DIR)/ $(addprefix -I,$(ALL_SRC_SUBDIRS))

TEST            = $(TEST_DIR)/$(NAME)_test.c

_OBJ            = $(NAME).o $(NAME)_test.o
OBJ             = $(patsubst %,$(ODIR)/%,$(_OBJ))

DEBUG_TARGET    = $(DEBUG_DIR)/$(NAME)_debug.out
RELEASE_TARGET  = $(RELEASE_DIR)/$(NAME)_release.out


define GET_DEPENDENCIES
$(shell $(CC) $(INCLUDE) -MM $(1) 2>/dev/null | \
	tr ' ' '\n'| \
	grep '\.h'| \
	sed 's/\.h/\.c/' | \
	xargs -I {} basename {} | sort | uniq)
endef

DEPEN_FILES    = $(call GET_DEPENDENCIES, $(MAIN_SRC))
SPECIFIC_SRC   = $(sort $(filter $(addprefix %, $(DEPEN_FILES)), $(ALL_SRC)) \
                 $(MAIN_SRC))

ADDITIONAL_SRC = $(sort $(notdir $(SPECIFIC_SRC:.c=.o)))

#-----------------------------------------------------------#
########################### RULES ###########################
#-----------------------------------------------------------#

%.o: %.c
	@$(CC) $(GD) -c $< -o $(notdir $@)

all: run clean

test:
	@echo "additional: $(ADDITIONAL_SRC)"
	@echo "include: $(INCLUDE)"
	@echo "VPATH: $(VPATH)"
#	echo "include: $(ALL_SRC)"

#$(NAME).o: $(TEST) $(SRC)
#	@$(CC) $(GD) -c $^
#	@echo "created object files"
	
obj: $(NAME).o
	
debug: $(TEST) $(ADDITIONAL_SRC)
	@$(CC) $(GD) $(TEST) $(ADDITIONAL_SRC) -o $(DEBUG_TARGET)
	@rm -f $(CURDIR)/*.o
	@echo "finished debug compilation"
	
run: debug
	@$(DEBUG_TARGET)

release: $(TEST) $(SRC) $(ADDITIONAL_SRC)
	@$(CC) $(GC) $(TEST) $(SRC) $(ADDITIONAL_SRC) -o $(RELEASE_TARGET)
	@echo "finished release compilation"

run_r: release
	@$(RELEASE_TARGET)

vlg: debug
	@valgrind $(VLG_FLAGS) $(DEBUG_TARGET)

.PHONY: vlg debug clean run obj release test
	
clean:
	@-rm $(SRC_DIR)/$(NAME).o $(RELEASE_DIR)/$(NAME)_release.out $(DEBUG_DIR)/$(NAME)_debug.out


