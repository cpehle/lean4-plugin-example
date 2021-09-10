# Detect Lean

ifndef LEAN_HOME
LEAN ?= lean
LEAN_HOME := $(shell $(LEAN) --print-prefix)
endif

LEAN_INCLUDE := $(LEAN_HOME)/include


# Config

MKPATH := mkdir -p
RMPATH := rm -rf

AR := ar
CXX	:= c++
EXTRA_CXX_FLAGS := -O1

SRC_DIR := src
HDR_DIR := include
OUT_DIR := build

HDRS := example.h

SRCS := example.cpp

LIB_NAME := ExampleC
LIB := lib${LIB_NAME}.a

OBJ_FILES := $(addprefix $(OUT_DIR)/,$(SRCS:.cpp=.o))
HDR_FILES := $(addprefix $(HDR_DIR)/,$(HDRS))

# Build Rules

all: lib

lib: $(OUT_DIR)/$(LIB)

$(OUT_DIR):
	$(MKPATH) $@

$(OUT_DIR)/$(LIB) : $(OBJ_FILES) | $(OUT_DIR)
	${AR} rcs $@ $^

$(OUT_DIR)/%.o : $(SRC_DIR)/%.cpp $(HDR_FILES) | $(OUT_DIR)
	$(CXX) -o $@ -c $< -I$(HDR_DIR) -I$(LEAN_INCLUDE) $(EXTRA_CXX_FLAGS)

clean:
	$(RMPATH) $(OUT_DIR)
