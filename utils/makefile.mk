# **************************************************************** user setup */
name        ?= default# file name
project     ?= ds# project name
git_dir     ?= git# git directory name

# additional directories containing headers and source files
additional_src_dirs ?= c ds projects utils system_programming

home        ?= $(shell echo $$home)
current_dir ?= $(shell echo $$curdir)

null   :=
space  := $(null) $(null)

# ************************************************ all directories & sources */
project_dir := $(home)/$(git_dir)/$(project)

all_src_dirs    := $(addprefix $(home)/$(git_dir)/, $(project) $(additional_src_dirs))

# recursively find all directories and subdirectories containing headers/sources
all_src_subdirs := $(sort $(shell find $(all_src_dirs) -type d 2>/dev/null))

vpath           := $(subst $(space),:,$(strip $(all_src_subdirs)))

# find all .c files across all depths
all_src         := $(sort $(shell find $(all_src_subdirs) -type f -name "*.c" 2>/dev/null))
all_src         := $(filter-out %/try.c %/structs.c, $(all_src))

# match main and test targets precisely
main_src        := $(firstword $(filter $(project_dir)/%/$(name).c, $(all_src)) $(filter %/$(name).c, $(all_src)))
test_src        := $(firstword $(filter $(project_dir)/%/$(name)_test.c $(project_dir)/%/test_$(name).c, $(all_src)) $(filter %/$(name)_test.c %/test_$(name).c, $(all_src)))

# active target source file (prefer test if present, otherwise main)
active_src      := $(if $(test_src),$(test_src),$(main_src))

# ********************************************** deep include resolution */
# find all headers to support deep traversal
all_headers := $(sort $(shell find $(all_src_subdirs) -type f -name "*.h" 2>/dev/null))

# awk transitive dependency resolver
# traces local #include "x.h" paths across both .c and .h files to build a complete dependency tree.
target_module_srcs := $(shell \
    awk -v srcs="$(active_src) $(if $(filter-out $(active_src),$(main_src)),$(main_src),)" \
        -v c_files="$(all_src)" -v h_files="$(all_headers)" ' \
    begin { \
        split(c_files, ca, " "); \
        for (i in ca) { \
            n = split(ca[i], pa, "/"); stem = pa[n]; sub(/\.c$$/, "", stem); \
            c_map[stem] = ca[i]; \
        } \
        split(h_files, ha, " "); \
        for (i in ha) { \
            n = split(ha[i], pa, "/"); stem = pa[n]; sub(/\.h$$/, "", stem); \
            h_map[stem] = ha[i]; \
        } \
        split(srcs, q, " "); \
        has_items = 0; \
        for (i in q) { \
            if (q[i] != "") { queue[q[i]] = 1; c_visited[q[i]] = 1; has_items = 1; } \
        } \
        while (has_items) { \
            has_items = 0; \
            for (k in next_q) delete next_q[k]; \
            for (f in queue) { \
                while ((getline line < f) > 0) { \
                    if (match(line, /#[ \t]*include[ \t]*"[^"]+\.h"/)) { \
                        s = substr(line, rstart, rlength); \
                        q1 = index(s, "\""); \
                        stem = substr(s, q1 + 1, length(s) - q1 - 3); \
                        if (stem in c_map && !c_visited[c_map[stem]]) { \
                            c_visited[c_map[stem]] = 1; next_q[c_map[stem]] = 1; has_items = 1; \
                        } \
                        if (stem in h_map && !h_visited[h_map[stem]]) { \
                            h_visited[h_map[stem]] = 1; next_q[h_map[stem]] = 1; has_items = 1; \
                        } \
                    } \
                } \
                close(f); \
            } \
            for (k in queue) delete queue[k]; \
            for (k in next_q) queue[k] = 1; \
        } \
        for (f in c_visited) print f; \
    }' 2>/dev/null \
)

# remove the active/test files from shared module list to get pure dependency modules
dep_module_srcs := $(filter-out $(active_src) $(main_src) %_test.c %/test_%.c, $(target_module_srcs))

# fallback just in case parsing failed entirely
ifeq ($(strip $(dep_module_srcs)),)
    ifeq ($(strip $(target_module_srcs)),)
        dep_module_srcs := $(filter-out $(active_src) $(main_src) %_test.c %/test_%.c, $(all_src))
    endif
endif

# ********************************************************* compilation flags */
cc            ?= gcc

include_flags := $(addprefix -i,$(all_src_subdirs))
cflags        ?= -ansi -pedantic-errors -wall -wextra -mmd -mp
vlgflags      ?= --leak-check=yes --track-origins=yes -s

# ***************************************************** target specific flags */
debug_flags   := -g
release_flags := -dndebug -o3
trgtflags     ?= $(cflags) $(include_flags)

# *************************************** target specific variables and paths */
debug_path    ?= $(project_dir)/bin/debug/
release_path  ?= $(project_dir)/bin/release/
archive_path  ?= $(current_dir)/

# shared library dependencies
dep_names     := $(notdir $(dep_module_srcs:.c=))
dylibs_db     := $(patsubst %,lib%_db.so,$(dep_names))
dylibs_rl     := $(patsubst %,lib%.so,$(dep_names))

# include auto-generated dependency files for precise rebuilds
-include $(wildcard $(debug_path)*.d $(release_path)*.d *.d)

# ********************************************************* logic rules */
%.o : %.c
	@echo "compiling static object: $<..."
	@$(cc) $(trgtflags) -c $< -o $@ -lm

$(debug_path)lib%_db.so : %.c
	@mkdir -p $(debug_path)
	@echo " -> updating debug shared object: $@"
	@$(cc) -fpic -shared $(cflags) $(debug_flags) $(include_flags) -mt $@ -mf $(debug_path)$*_db.d $< -o $@ -lm

$(release_path)lib%.so : %.c
	@mkdir -p $(release_path)
	@echo " -> updating release shared object: $@"
	@$(cc) -fpic -shared $(cflags) $(release_flags) $(include_flags) -mt $@ -mf $(release_path)$*.d $< -o $@ -lm

# ************************************************************** main targets */
.phony: test debug dbso run release rlso runrlso objects clean help runso

test:
	@echo "name:            $(name)"
	@echo "active_src:      $(active_src)"
	@echo "dep_module_srcs: $(dep_module_srcs)"
	@echo "dylibs_db count: $(words $(dylibs_db))"
	@echo "dylibs_rl count: $(words $(dylibs_rl))"
	@echo ""

debug: trgtflags = $(cflags) $(debug_flags) $(include_flags)
debug: trgtpath = $(debug_path)
debug: $(notdir $(dep_module_srcs:.c=.o)) $(notdir $(main_src:.c=.o)) $(notdir $(active_src:.c=.o))
	@mkdir -p $(trgtpath)
	@$(cc) $(trgtflags) $^ -o $(trgtpath)$(name).out -lm
	@rm -f *.o *.d
	@echo "debug build done."

dbso: trgtflags = $(cflags) $(debug_flags) $(include_flags)
dbso: trgtpath = $(debug_path)
dbso: $(addprefix $(debug_path),$(dylibs_db))
	@echo "linking test binary against relevant debug shared libraries..."
	@$(cc) $(trgtflags) $(active_src) $(main_src) \
		-l$(trgtpath) \
		-wl,-rpath,$(trgtpath) \
		-wl,--start-group $(patsubst lib%_db.so,-l%_db,$(dylibs_db)) \
		-wl,--end-group -o $(trgtpath)$(name).out -lm
	@echo "finished dynamic debug compilation for $(name)."

rlso: trgtflags = $(cflags) $(release_flags) $(include_flags)
rlso: trgtpath = $(release_path)
rlso: $(addprefix $(release_path),$(dylibs_rl))
	@echo "linking test binary against relevant release shared libraries..."
	@$(cc) $(trgtflags) $(active_src) $(main_src) \
		-l$(trgtpath) \
		-wl,-rpath,$(trgtpath) \
		-wl,--start-group $(patsubst lib%.so,-l%,$(dylibs_rl)) \
		-wl,--end-group -o $(trgtpath)$(name).out -lm
	@echo "finished dynamic release compilation for $(name)."

runso: dbso
	@echo "$(name) (debug shared) is running..."
	@$(debug_path)$(name).out

runrlso: rlso
	@echo "$(name) (release shared) is running..."
	@$(release_path)$(name).out

run: debug
	@echo "$(name) is running..."
	@$(debug_path)$(name).out

clean:
	@rm -f *.o *.d
	@rm -f $(debug_path)*.out $(release_path)*.out
	@rm -f $(debug_path)*.so $(release_path)*.so
	@rm -f $(debug_path)*.d $(release_path)*.d
	@echo "cleaned up build files."

