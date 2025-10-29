# -----------------------------------------------------------------------------
# VARIABLEs
# -----------------------------------------------------------------------------
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MKFILE_DIR := $(dir $(MKFILE_PATH))

APP_SRCS += $(MKFILE_DIR)/main.c

# -----------------------------------------------------------------------------
# FLAGs
# -----------------------------------------------------------------------------
ifdef 	USE_CLUSTER
APP_CFLAGS += -DCLUSTER -DNUM_CLUSTER=$(USE_CLUSTER)
ifdef 	NUM_CORES
APP_CFLAGS += -DNUM_CORES=$(NUM_CORES)
else	# NUM_CORES
APP_CFLAGS += -DNUM_CORES=1
endif	# NUM_CORES
endif	# USE_CLUSTER

APP_CFLAGS += -DTARGET_IS_PULP_OPEN
APP_CFLAGS += -O3 -g -I$(INC_DIR) -I$(DATA_DIR) -I$(COMMON_DIR)
APP_LDFLAGS += -O3 -g

# -----------------------------------------------------------------------------
# RULEs
# -----------------------------------------------------------------------------
override CURDIR := $(patsubst %/,%,$(MKFILE_DIR))
include $(RULES_DIR)/pmsis_rules.mk

# Extend "clean" rule to cleanup also test objects
clean::
	@echo "RM  BUILD/"
	$(V)rm -rf $(CURDIR)/BUILD
