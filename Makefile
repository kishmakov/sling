# dirs
INCLUDES = ./include .
OBJ_DIR = obj
SRC_DIR = src

# file sets
CPP_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(strip $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(CPP_FILES))))

# options
CC = g++
CFLAGS = -O0 -g -fPIC -std=c++0x $(WARNING_FLAGS) $(addprefix -I, $(INCLUDES))
LFLAGS = -pthread

# Main Targets
##############

all: verbose-link

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f sling

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
$(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(1))): $(1)
	$(CC) $(CFLAGS) -c $$< -o $$@
endef

$(foreach file, $(CPP_FILES), $(eval $(call rul_gen, $(file))))

link:
	$(CC) -o sling $(OBJ_FILES) $(LFLAGS)
