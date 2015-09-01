# dirs
INCLUDES = src
OBJ_DIR = obj
SRC_DIR = src

# file sets
SOURCE_FILES = $(wildcard $(SRC_DIR)/*.c)
SOURCE_FILES += $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(strip $(patsubst %.c, $(OBJ_DIR)/%.o, $(subst /,_,$(SOURCE_FILES))))

# options
CC = clang-3.5
CFLAGS = -O0 -g -fPIC -std=c11 $(WARNING_FLAGS) $(addprefix -I, $(INCLUDES))
LFLAGS = -pthread

# Main Targets
##############

all: verbose-link

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f run-tests

# Internal Targets
##################

verbose-link: verbose-compile announce-link link

verbose-compile: announce-compile create-dirs $(OBJ_FILES)

announce-link:
	@echo "*** link ***"

announce-compile:
	@echo "*** compile ***"

create-dirs:
	@mkdir -p $(OBJ_DIR)

# pattern matching for obj files
define rul_gen
$(patsubst %.c, $(OBJ_DIR)/%.o, $(subst /,_,$(1))): $(1)
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(foreach file, $(SOURCE_FILES), $(eval $(call rul_gen, $(file))))

link:
	$(CC) -o run-tests $(OBJ_FILES) $(LFLAGS)
