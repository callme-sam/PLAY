SRC_DIR = ../../source/vector_dot/
INC_DIR = ../../include/
DATA_DIR = test_data/
COMMON_DIR = ../common

APP = vector-dot-test
APP_SRCS += main.c $(wildcard $(SRC_DIR)/*.c) $(wildcard $(COMMON_DIR)/*.c)

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

APP_CFLAGS += -Os -g -I$(INC_DIR) -I$(DATA_DIR) -I$(COMMON_DIR)
APP_LDFLAGS += -Os -g


include $(RULES_DIR)/pmsis_rules.mk

# Extend "clean" rule to cleanup also test objects
clean::
	@echo "RM  BUILD/PULP/source"
	$(V)rm -rf BUILD/PULP/source