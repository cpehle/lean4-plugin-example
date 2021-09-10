# Detect Lean

LEAN  ?= lean
LEANC ?= leanc


# Config

MV := mv
RM := rm

MKPATH := mkdir -p
RMPATH := ${RM} -rf

OUT_DIR := build

LIB_NAME := Example
LIB_DIR := ../build/lib
LIB := lib${LIB_NAME}.a

C_LIB_NAME := ExampleC
C_LIB_DIR := ../cc/build
C_LIB := lib${C_LIB_NAME}.a

PLUGIN := ExamplePlugin
PLUGIN_LIB := ${PLUGIN}.dll

LEAN_PATH=../build

# Build Rules

all: plugin

$(OUT_DIR):
	$(MKPATH) $@

clean:
	$(RMPATH) $(OUT_DIR)

# Plugin Build

plugin: $(OUT_DIR)/${PLUGIN_LIB}

$(OUT_DIR)/${PLUGIN_LIB}: $(OUT_DIR)/${PLUGIN}.c $(C_LIB_DIR)/$(C_LIB) $(LIB_DIR)/$(LIB) | $(OUT_DIR)
# rename old lib in case it can't be replaced (e.g., because it is in use)
	-${MV} $@ $@.tmp
	${LEANC} -shared -o $@ $< -L${LIB_DIR} -Wl,--whole-archive -l$(LIB_NAME) -Wl,--no-whole-archive -L${C_LIB_DIR} -l${C_LIB_NAME}
# try to delete old lib
	${RM} -f $@.tmp


$(OUT_DIR)/${PLUGIN}.c: ${PLUGIN}.lean | $(OUT_DIR)
	LEAN_PATH=${LEAN_PATH} $(LEAN) -c $@ $<
