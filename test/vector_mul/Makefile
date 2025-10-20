# -----------------------------------------------------------------------------
# VARIABLEs
# -----------------------------------------------------------------------------
CURRENT_DIR := $(shell pwd)

SRC_DIR_REL = ../../source/vector_mul/
INC_DIR_REL = ../../include
DATA_DIR_REL = test_data
COMMON_DIR_REL = ../common

SRC_DIR = $(abspath $(CURRENT_DIR)/$(SRC_DIR_REL))
INC_DIR = $(abspath $(CURRENT_DIR)/$(INC_DIR_REL))
DATA_DIR = $(abspath $(CURRENT_DIR)/$(DATA_DIR_REL))
COMMON_DIR = $(abspath $(CURRENT_DIR)/$(COMMON_DIR_REL))

APP = vector-mul-test_data
APP_SRCS_REL = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(COMMON_DIR)/*.c)
APP_SRCS := $(foreach file, $(APP_SRCS_REL), $(abspath $(file)))

# -----------------------------------------------------------------------------
# FLAGs
# -----------------------------------------------------------------------------
ifdef PRINT_DATA
APP_CFLAGS += -DPRINT_DATA
endif

ifdef STATS
APP_CFLAGS += -DSTATS
endif

ifdef ENABLE_LOGGING
APP_CFLAGS += -DENABLE_LOGGING
endif

# -----------------------------------------------------------------------------
# TARGETs
# -----------------------------------------------------------------------------
ifeq ($(TARGET), PULP_OPEN)
include pulp-open/Makefile
else ifeq ($(TARGET), SPATZ)
include spatz/Makefile
else
$(error Invalid TARGET: $(TARGET))
endif
