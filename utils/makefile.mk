# **************************************************************** User Setup */
NAME    ?= default# File name
PROJECT ?= ds# Project name
GIT_DIR ?= git# GIT directory name


# ********** additional directories for possibly needed source files ********* #
ADDITIONAL_SRC_DIRS ?= c ds projects utils system_programming

HOME        ?= $(shell echo $$HOME)
CURRENT_DIR ?= $(shell echo $$CURDIR)

null  :=
space := $(null) $(null)


# ************************************************ All dependencies SRC files */
PROJECT_DIR := $(HOME)/$(GIT_DIR)/$(PROJECT)

ALL_SRC_DIRS    := $(addprefix $(HOME)/$(GIT_DIR)/, \
                   $(PROJECT) $(ADDITIONAL_SRC_DIRS))
ALL_SRC_SUBDIRS := $(sort $(shell find $(ALL_SRC_DIRS) -type d 2>/dev/null))

VPATH       := $(subst $(space),:,$(strip $(ALL_SRC_SUBDIRS)))

ALL_SRC     := $(sort $(shell find $(ALL_SRC_SUBDIRS) -name "*.c" \
               2>/dev/null))
ALL_SRC     := $(filter-out %/try.c %/structs.c, $(ALL_SRC))

MAIN_SRC    := $(filter %/$(NAME).c, $(ALL_SRC))
TEST_SRC    := $(filter %/$(NAME)_test.c %/test_$(NAME).c, $(ALL_SRC))


# ********************************************************* Compilation flags */
CC            ?= gcc
INCLUDE_FLAGS ?= -I$(PROJECT_DIR)/inc $(addprefix -I,$(ALL_SRC_SUBDIRS))
CFLAGS        ?= -ansi -pedantic-errors -Wall -Wextra
VLGFLAGS      ?= --leak-check=yes --track-origins=yes -s
CALGFLAGS     ?= --tool=callgrind --dump-instr=yes --collect-jumps=yes \
                 --dump-line=yes --separate-recs=1 \
                 --callgrind-out-file=$(TRGTPATH)$(NAME).callgrind.out
CACGFLAGS     ?= --tool=cachegrind --branch-sim=yes \
                 --cachegrind-out-file=$(TRGTPATH)$(NAME).cachegrind.out
MSIFFLAGS     ?= --tool=massif --massif-out-file=$(TRGTPATH)$(NAME).massif.out


# ***************************************************** target specific flags */
DEBUG_FLAGS   := -g
RELEASE_FLAGS := -DNDEBUG -O3
TRGTFLAGS     ?= $(CFLAGS) $(INCLUDE_FLAGS)


# *************************************** Target specific Variables and Paths */
DEBUG_PATH   ?= $(PROJECT_DIR)/bin/debug/
RELEASE_PATH ?= $(PROJECT_DIR)/bin/release/
ARCHIVE_PATH ?= $(CURRENT_DIR)/

define GET_DEPENDENCIES
$(shell $(CC) $(INCLUDE_FLAGS) -MM $(1) 2>/dev/null | \
	tr ' ' '\n' | \
	grep '\.h' | \
	xargs -n 1 basename | \
	sed 's/\.h/\.c/' | \
	sort | uniq)
endef

INITIAL_DEPS    := $(call GET_DEPENDENCIES, $(MAIN_SRC) $(TEST_SRC))
INITIAL_SRC     := $(sort $(filter $(addprefix %, $(INITIAL_DEPS)), $(ALL_SRC)))
ALL_DEPEN_FILES := $(call GET_DEPENDENCIES, $(MAIN_SRC) $(TEST_SRC) \
                   $(INITIAL_SRC) $(sort $(filter $(addprefix %, \
                   $(call GET_DEPENDENCIES, $(INITIAL_SRC))), $(ALL_SRC))))
SPECIFIC_SRC    := $(sort $(filter $(addprefix %, $(ALL_DEPEN_FILES)), \
                   $(ALL_SRC)) $(MAIN_SRC) $(TEST_SRC))

PU_NAME := personal_utils
PU_FILE := lib$(PU_NAME).so

DEP_NAMES := $(filter-out $(NAME)_test test_$(NAME), \
             $(notdir $(SPECIFIC_SRC:.c=)))
DYLIBS    := $(patsubst %,lib%.so,$(DEP_NAMES))
TEST      := $(notdir $(TEST_SRC))


# ************************************************************* Objects modes */
OBJECTS_MODE ?= 0

ifeq ($(OBJECTS_MODE), 1)
    OBJS := $(NAME).o
else ifeq ($(OBJECTS_MODE), 2)
    OBJS := $(NAME)_test.o
else ifeq ($(OBJECTS_MODE), 3)
    OBJS := $(NAME).o $(NAME)_test.o
else
    OBJS := $(sort $(notdir $(SPECIFIC_SRC:.c=.o)))
endif


# ********************************************************* Logic Rules */
%.o : %.c
	@echo "Compiling static object: $<..."
	@$(CC) $(TRGTFLAGS) -c $< -o $@ -lm

$(DEBUG_PATH)lib%.so : %.c
	@mkdir -p $(DEBUG_PATH)
	@echo " -> Updating debug shared object: $@"
	@$(CC) -fPIC -shared $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS) $< -o $@ -lm

$(RELEASE_PATH)lib%.so : %.c
	@mkdir -p $(RELEASE_PATH)
	@echo " -> Updating release shared object: $@"
	@$(CC) -fPIC -shared $(CFLAGS) $(RELEASE_FLAGS) $(INCLUDE_FLAGS) \
	$< -o $@ -lm

%lib%.so : %.h
	@echo '#include "$<"' | $(CC) $(TRGTFLAGS) -fPIC -x c - -shared -o \
	$(TRGTPATH)$(notdir $@)
	@echo "Header-only Dynamic library named $@ created."

%.a : %.o
	@ar rcs $(TRGTPATH)$(NAME).a $^


# ************************************************************** Main targets */
.PHONY: test debug dbso pic valgrind run release rlso objects archive \
	analysis clean help runso

test: OBJS := $(sort $(notdir $(TEST_SRC:.c=.o)))
test:
	@echo "DYLIBS: $(DYLIBS)"
	@echo "INITIAL_SRC: $(INITIAL_SRC)"
	@echo "INITIAL_DEPS: $(INITIAL_DEPS)"
	@echo "ALL_DEPEN_FILES: $(ALL_DEPEN_FILES)"
	@echo "OBJS: $(OBJS)"
	@echo "VPATH: $(VPATH)"
	@echo ""

debug: TRGTFLAGS = $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)
debug: TRGTPATH = $(DEBUG_PATH)
debug: $(OBJS)
	@echo "OBJS: $(OBJS)"
	@mkdir -p $(TRGTPATH)
	@$(CC) $(TRGTFLAGS) $(OBJS) -o $(TRGTPATH)$(NAME).out -lm
	@rm -f $(CURRENT_DIR)/*.o
	@echo "Debug build done."

dbso: TRGTFLAGS = $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDE_FLAGS)
dbso: TRGTPATH = $(DEBUG_PATH)
dbso: $(addprefix $(DEBUG_PATH),$(DYLIBS))
	@echo "Linking test binary..."
	@$(CC) $(TRGTFLAGS) $(TEST_SRC) \
		-L$(TRGTPATH) \
		-Wl,-rpath,$(TRGTPATH) \
		-Wl,--start-group $(patsubst lib%.so,-l%,$(DYLIBS)) \
		-Wl,--end-group -o $(TRGTPATH)$(NAME).out -lm
	@rm -f $(CURRENT_DIR)/*.o
	@echo "finished dynamic debug compilation for $(NAME)."

runso: dbso
	@echo "$(NAME) is -----------------------------> running..."
	@echo ""
	@$(DEBUG_PATH)$(NAME).out
	@echo "$(NAME) -----------------------------> done running."

pic: $(SPECIFIC_SRC)
	@$(CC) $(GD_PIC) $(SPECIFIC_SRC)

valgrind: debug
	@echo "Valgrind start..."
	@valgrind $(VLGFLAGS) $(DEBUG_PATH)$(NAME).out
	@echo "Valgrind done."

run: debug
	@echo "$(NAME) is -----------------------------> running..."
	@echo ""
	@$(DEBUG_PATH)$(NAME).out
	@echo "$(NAME) -----------------------------> done running."

release: TRGTFLAGS = $(CFLAGS) $(RELEASE_FLAGS)    
release: $(OBJS)
	@mkdir -p $(RELEASE_PATH)
	@$(CC) $(TRGTFLAGS) $(OBJS) -o $(RELEASE_PATH)$(NAME).out
	@echo "Production build done."

rlso: TRGTFLAGS = $(CFLAGS) $(RELEASE_FLAGS) $(INCLUDE_FLAGS)
rlso: TRGTPATH = $(RELEASE_PATH)
rlso: $(addprefix $(RELEASE_PATH),$(DYLIBS))
	@echo "Linking test binary..."
	@$(CC) $(TRGTFLAGS) $(TEST_SRC) \
		-L$(TRGTPATH) \
		-Wl,-rpath,$(TRGTPATH) \
		-Wl,--start-group $(patsubst lib%.so,-l%,$(DYLIBS)) \
		-Wl,--end-group -o $(TRGTPATH)$(NAME).out -lm
	@rm -f $(CURRENT_DIR)/*.o
	@echo "finished dynamic release compilation for $(NAME)."

objects: $(OBJS)
	@echo "object created at $(OBJS)."

archive: $(NAME).o
	@ar rcs $(ARCHIVE_PATH)$(NAME).a $<
	@echo "Static library named $(NAME).a created at $(ARCHIVE_PATH)."

analysis: TRGTPATH = $(DEBUG_PATH)
analysis: dbso
	@echo "Valgrind deep analysis (cachegrind, callgrind, massif) start..."
	@mkdir -p $(TRGTPATH)
	@echo " -> Running Callgrind..."
	@valgrind $(CALGFLAGS) $(TRGTPATH)$(NAME).out > /dev/null 2>&1
	
	@echo " -> Running Cachegrind..."
	@valgrind $(CACGFLAGS) $(TRGTPATH)$(NAME).out > /dev/null 2>&1
	
	@echo " -> Text logs generated at $(TRGTPATH)."
	@callgrind_annotate --auto=yes $(TRGTPATH)$(NAME).callgrind.out > $(TRGTPATH)callgrind_report.txt
	@cg_annotate --auto=yes $(TRGTPATH)$(NAME).cachegrind.out > $(TRGTPATH)cachegrind_report.txt
	
	@echo " -> Running Massif (Heap Profiling)..."
	@valgrind $(MSIFFLAGS) $(TRGTPATH)$(NAME).out > /dev/null 2>&1
	@ms_print $(TRGTPATH)$(NAME).massif.out > $(TRGTPATH)massif_report.txt

	@echo " -> Launching KCachegrind in background..."
	@if command -v kcachegrind >/dev/null 2>&1; \
	then kcachegrind $(TRGTPATH)$(NAME).callgrind.out $(TRGTPATH)$(NAME).cachegrind.out >/dev/null 2>&1 & \
	else \
		echo " [!] KCachegrind GUI not found. View text reports in $(TRGTPATH)*_report.txt"; \
	fi
	@echo "Valgrind deep analysis (cachegrind, callgrind, massif) completed."

clean:
	@rm -f $(PROJECT_DIR)/src/*.o $(PROJECT_DIR)/test/*.o $(CURRENT_DIR)/*.o
	@rm -f $(DEBUG_PATH)*.out $(RELEASE_PATH)*.out
	@rm -f $(ARCHIVE_PATH)*.a $(DEBUG_PATH)*.so $(RELEASE_PATH)*.so
	@rm -f $(DEBUG_PATH)*.callgrind.out $(DEBUG_PATH)*.cachegrind.out $(DEBUG_PATH)*.massif.out
	@rm -f $(DEBUG_PATH)*_report.txt
	@echo "all cleaned up."

help:
	@echo "=========================================================="
	@echo "  Project Makefile Help"
	@echo "=========================================================="
	@echo "  Usage: make NAME=[module_name] [target] [OBJECTS_MODE=n]"
	@echo ""
	@echo "  Targets:"
	@echo "    debug    : Build with debug symbols (-g)"
	@echo "    valgrind : Build and run with memory leak tracking"
	@echo "    run      : Build and execute the debug binary"
	@echo "    release  : Build with high optimization (-O3) without debug"
	@echo "    analysis : Run comprehensive profiling (Callgrind, Cachegrind, Massif)"
	@echo "    objects  : Built via different modes (OBJECTS_MODE):"
	@echo "          (default)->0 - Builds module, test, and dependencies"
	@echo "                    1 - Builds [NAME].o only"
	@echo "                    2 - Builds [NAME]_test.o only"
	@echo "                    3 - Builds [NAME].o and [NAME]_test.o"
	@echo "    archive  : Create static library (.a) from source"
	@echo "    clean    : Remove all binaries and object files"
	@echo "=========================================================="

