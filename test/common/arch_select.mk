
# Helper makefile fragment to centralize selection of arch-specific
# implementation files and to prevent wildcard collection from
# accidentally including all arch implementations.
#
# Usage (from test/*/Makefile):
#   include ../common/arch_select.mk
#   # After APP_SRCS_REL is defined by the test Makefile
#   FILTER_APP_SRCS_REL := $(call arch_filter,$(APP_SRCS_REL))
#   APP_SRCS := $(foreach file, $(FILTER_APP_SRCS_REL), $(abspath $(file)))
#   # Register the arch implementation for this kernel:
#   $(call add_arch_impl,vector_mul)

# Filter out any files under an "arch" subdirectory from a list of paths.
# Try multiple patterns to be robust across make implementations.
arch_filter = $(filter-out %/arch/%.c $(filter-out %/arch/%,$(1)),$(1))

# Determine arch suffix based on TARGET. Defaults to empty.
ifeq ($(TARGET),PULP_OPEN)
ARCH_SUFFIX = pulp_open
else ifeq ($(TARGET),SPATZ)
ARCH_SUFFIX = spatz
else
ARCH_SUFFIX =
endif

# call: $(call add_arch_impl,vector_mul)
# Appends the arch implementation file to APP_SRCS using $(eval).
add_arch_impl = $(eval APP_SRCS += $(abspath $(CURRENT_DIR)/../../source/$(1)/arch/$(1)_$(ARCH_SUFFIX).c))
