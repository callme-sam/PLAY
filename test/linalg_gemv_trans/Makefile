SRC_DIR = ../../source/
SRC_SUB_DIRS = linalg_gemv_trans vector_memcpy vector_scale vector_set_all
INC_DIR = ../../include
DATA_DIR = test_data
COMMON_DIR = ../common

APP = linalg-gemv-trans-test
APP_SRCS += main.c $(foreach dir, $(SRC_SUB_DIRS), $(wildcard $(SRC_DIR)/$(dir)/*.c)) $(wildcard $(COMMON_DIR)/*.c)

ifdef USE_CLUSTER
APP_CFLAGS += -DCLUSTER -DNUM_CLUSTER=$(USE_CLUSTER)
ifdef NUM_CORES
APP_CFLAGS += -DNUM_CORES=$(NUM_CORES)
else	# NUM_CORES
APP_CFLAGS += -DNUM_CORES=1
endif	# NUM_CORES
endif	# USE_CLUSTER

ifdef PRINT_DATA
APP_CFLAGS += -DPRINT_DATA
endif	# PRINT_DATA

ifdef STATS
APP_CFLAGS += -DSTATS
endif	#STATS

APP_CFLAGS += -O3 -g -I$(INC_DIR) -I$(DATA_DIR) -I$(COMMON_DIR)
APP_LDFLAGS += -O3 -g


include $(RULES_DIR)/pmsis_rules.mk

# Extend "clean" rule to cleanup also test objects
clean::
	@echo "RM  BUILD/PULP/source"
	$(V)rm -rf BUILD/PULP/source
