# dirs

UNIT_TESTS_BINARY = unit-tests
OBJ_DIR = obj
SRC_DIR = src
TST_DIR = tests

INCLUDES = $(SRC_DIR)
TST_INCLUDES = $(SRC_DIR) $(TST_DIR)

# file sets
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SRC_FILES += $(wildcard $(SRC_DIR)/*/*.c)

TST_SRC_FILES = $(wildcard $(TST_DIR)/*.c)
TST_SRC_FILES += $(wildcard $(TST_DIR)/*/*.c)

OBJ_FILES = $(strip $(patsubst %.c, $(OBJ_DIR)/%.o, $(subst /,_,$(SRC_FILES))))
TST_OBJ_FILES = $(strip $(patsubst %.c, $(OBJ_DIR)/%.o, $(subst /,_,$(TST_SRC_FILES))))

# options
CC = clang-3.5
COMMON_CFLAGS = -O0 -g -fPIC -std=c11 $(WARNING_FLAGS)
# COMMON_CFLAGS += -D NDEBUG
CFLAGS = $(COMMON_CFLAGS) $(addprefix -I, $(INCLUDES))
TST_CFLAGS = $(COMMON_CFLAGS) $(addprefix -I, $(TST_INCLUDES))
LFLAGS = -pthread
TST_LFLAGS = $(LFLAGS) -lcmocka

# Main Targets
##############

all: verbose-sling

test: verbose-sling verbose-test run-unit-test

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(UNIT_TESTS_BINARY)
	@rm -f sling

# Internal Targets
##################

verbose-sling: verbose-compile-sling verbose-link-sling

verbose-test: verbose-compile-test verbose-link-test

verbose-compile-sling: announce-compile-sling create-dirs $(OBJ_FILES)

verbose-compile-test: announce-compile-test $(TST_OBJ_FILES)

verbose-link-sling: announce-link-sling

verbose-link-test: announce-link-test link-test

announce-compile-sling:
	@echo "*** compile sling ***"

announce-compile-test:
	@echo "*** compile tests ***"

announce-link-sling:
	@echo "*** link sling ***"

announce-link-test:
	@echo "*** link tests ***"

create-dirs:
	@mkdir -p $(OBJ_DIR)

# pattern matching for obj files
define rul_gen
$(patsubst %.c, $(OBJ_DIR)/%.o, $(subst /,_,$(1))): $(1)
	$(CC) $(2) -c $$< -o $$@
endef

$(foreach file, $(SRC_FILES), $(eval $(call rul_gen, $(file), $(CFLAGS))))
$(foreach file, $(TST_SRC_FILES), $(eval $(call rul_gen, $(file), $(TST_CFLAGS))))

link-test:
	$(CC) -o $(UNIT_TESTS_BINARY) $(TST_OBJ_FILES) $(OBJ_FILES) $(TST_LFLAGS)

run-unit-test:
	./$(UNIT_TESTS_BINARY)