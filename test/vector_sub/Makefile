SRC_DIR = ../../source/vector_sub/
INC_DIR = ../../include/
DATA_DIR = test_data/
COMMON_DIR = ../common

APP = vector-sub-test
APP_SRCS := main.c $(wildcard $(SRC_DIR)/*.c) $(wildcard $(COMMON_DIR)/*.c)

ifdef PRINT_DATA
APP_CFLAGS += -DPRINT_DATA
endif	# PRINT_DATA

ifdef STATS
APP_CFLAGS += -DSTATS
endif	#STATS

ifdef ENABLE_LOGGING
APP_CFLAGS += -DENABLE_LOGGING
endif # ENABLE_LOGGING

############################################################################################
ifeq ($(TARGET), SPATZ)
$(info TARGET IS SPATZ)

ifeq ($(GVSOC_PATH),)
$(error GVSOC_PATH is not set)
endif

ifeq ($(LLVM_PATH),)
$(error LLVM_PATH is not set)
endif

ifeq ($(GCC_PATH),)
$(error GCC_PATH is not set)
endif

ifeq ($(SPATZ_SW_DIR),)
$(error SPATZ_SW_PATH is not set)
endif

CMAKE_COMMAND := cmake
MAKE_COMMAND := make
SPATZ_BUILD_DIR := BUILD/spatz
empty :=
space := $(empty) $(empty)
CMAKE_APP_SRCS := $(subst $(space),;,$(strip $(APP_SRCS)))
CMAKE_APP_CFLAGS := $(subst $(space),;,$(strip $(APP_CFLAGS)))
$(info $(CMAKE_APP_SRCS))

CMAKE_CONFIG_COMMAND := $(CMAKE_COMMAND) \
	-S . -B $(SPATZ_BUILD_DIR) \
	-DLLVM_PATH=$(LLVM_PATH) \
	-DGCC_PATH=/$(GCC_PATH) \
	-DAPP=$(APP) \
	-DSPATZ_SW_DIR=$(SPATZ_SW_DIR) 	\
	-DPRJ_SRCS="$(CMAKE_APP_SRCS)" \
	-DAPP_CFLAGS="$(CMAKE_APP_CFLAGS)" \
	-DPYTHON=python3 \
	-DBUILD_TESTS=ON \
	-DSPATZ_CLUSTER_CFG=spatz_cluster.default.dram.hjson \
	-DMEM_DRAM_ORIGIN=2147483648 \
	-DMEM_DRAM_SIZE=2147483648 \
	-DSNRT_BASE_HARTID=0 \
	-DSNRT_CLUSTER_CORE_NUM=2 \
	-DSNRT_TCDM_START_ADDR=1048576 \
	-DSNRT_CLUSTER_OFFSET=0 \
	-DSNRT_TCDM_SIZE=131072 \
	-DSNRT_NFPU_PER_CORE=4

all: build

$(SPATZ_BUILD_DIR):
	mkdir -p $(SPATZ_BUILD_DIR)

config: $(SPATZ_BUILD_DIR)
	$(CMAKE_CONFIG_COMMAND)

build: config
	$(MAKE_COMMAND) -C $(SPATZ_BUILD_DIR)

run: build
	cd $(SPATZ_BUILD_DIR) && \
	$(GVSOC_PATH) \
	--target spatz \
	--binary $(APP) \
	run

.PHONY: all config build run clean

############################################################################################
else	# PLATFORM CLUSTER / FABRIC CONTROLLER

ifdef USE_CLUSTER
$(info TARGET IS CLUSTER)
APP_CFLAGS += -DCLUSTER -DNUM_CLUSTER=$(USE_CLUSTER)
ifdef NUM_CORES
APP_CFLAGS += -DNUM_CORES=$(NUM_CORES)
else	# NUM_CORES
APP_CFLAGS += -DNUM_CORES=1
endif	# NUM_CORES
else	# USE_CLUSTER
$(info TARGET IS FABRIC CONTROLLER)
endif	# USE_CLUSTER

APP_CFLAGS += -O3 -g -I$(INC_DIR) -I$(DATA_DIR) -I$(COMMON_DIR)
APP_LDFLAGS += -O3 -g


include $(RULES_DIR)/pmsis_rules.mk

endif	# PLATFORM

clean::
	rm -rf BUILD
