
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
TEST_DIR    = $(SRC_DIR)/$(PROJECT)/test
BIN_DIR     = $(SRC_DIR)/$(PROJECT)/bin
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
GD_PIC    = $(GD) -fPIC -c
GD_SO     = $(GD) -shared
GC        = $(FLAGS) -DNDEBUG -O3
GC_PIC    = $(GC) -fPIC -c
GC_SO     = $(GC) -shared
VLG_FLAGS = --leak-check=yes --track-origins=yes

#----------------------------------------------------------------------------#
########################### FILE NAMES & LOCATIONS ###########################
#----------------------------------------------------------------------------#

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
ADDITIONAL_SO = $(patsubst %.o, %.so, $(ADDITIONAL_SRC))
ADDITIONAL_LIBSO = $(addprefix lib, $(ADDITIONAL_SO))

#-----------------------------------------------------------#
########################### RULES ###########################
#-----------------------------------------------------------#

%.o: %.c
	@$(CC) $(GD) -c $< -o $(notdir $@)

lib%.so: %.o
	@$(CC) $(GD_SO) -o $(DEBUG_DIR)/$(notdir $@) $<

all: run clean

test:
	@echo "additional: $(ADDITIONAL_SRC)"
	@echo "include: $(INCLUDE)"
	@echo "VPATH: $(VPATH)"
	@echo "ADDITIONAL:" $(ADDITIONAL_SO)
	@echo "newmakefile"
	@echo "additional so: "$(patsubst %.so,-l%,$(ADDITIONAL_SO))
#	echo "include: $(ALL_SRC)"
	
obj: $(NAME).o
	
debug: $(TEST) $(ADDITIONAL_SRC)
	@$(CC) $(GD) $(TEST) $(ADDITIONAL_SRC) -o $(DEBUG_TARGET)
	@rm -f $(CURDIR)/*.o
	@echo "finished debug compilation"
	
debug_so: pic $(ADDITIONAL_LIBSO) $(TEST)
	@$(CC) $(GD) $(TEST) -Wl,--start-group -L$(DEBUG_DIR) $(patsubst %.so,-l%,$(ADDITIONAL_SO)) -Wl,--end-group -o $(DEBUG_TARGET)
	@rm -f $(CURDIR)/*.o
	@echo "finished dynamic debug compilation"

pic: $(SPECIFIC_SRC)
	@$(CC) $(GD_PIC) $(SPECIFIC_SRC)
	
run: debug
	@$(DEBUG_TARGET)

release_so: pic $(ADDITIONAL_LIBSO) $(TEST)
	@$(CC) $(GC) $(TEST) -Wl,--start-group -L$(DEBUG_DIR) $(patsubst %.so,-l%,$(ADDITIONAL_SO)) -Wl,--end-group -o $(DEBUG_TARGET)
	@rm -f $(CURDIR)/*.o
	@echo "finished dynamic debug compilation"

release: $(TEST) $(ADDITIONAL_SRC)
	@$(CC) $(GC) $(TEST) $(ADDITIONAL_SRC) -o $(RELEASE_TARGET)
	@rm -f $(CURDIR)/*.o
	@echo "finished release compilation"

run_r: release
	@$(RELEASE_TARGET)

run_so: debug_so
	@LD_LIBRARY_PATH=$(DEBUG_DIR) $(DEBUG_TARGET)
	@$(DEBUG_TARGET)
	
run_so_r: release_so
	@LD_LIBRARY_PATH=$(DEBUG_DIR) $(DEBUG_TARGET)
	@$(DEBUG_TARGET)	

vlg: debug
	@valgrind $(VLG_FLAGS) $(DEBUG_TARGET)

.PHONY: vlg debug clean run obj release test debug_so pic run_r
	
clean:
	@-rm $(SRC_DIR)/$(NAME).o $(RELEASE_DIR)/$(NAME)_release.out $(DEBUG_DIR)/$(NAME)_debug.out


