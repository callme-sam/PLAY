cmake_minimum_required(VERSION 3.13)

message(STATUS "spatz sw dir: ${SPATZ_SW_DIR}")
message(STATUS "PRJ_SRC: ${PRJ_SRCS}")

set(SNITCH_SOFTWARE_DIR ${SPATZ_SW_DIR})
list(APPEND CMAKE_MODULE_PATH ${SNITCH_SOFTWARE_DIR}/cmake)
set(CMAKE_TOOLCHAIN_FILE toolchain-llvm)
set(SNITCH_RUNTIME snRuntime-cluster CACHE STRING "")
set(SNRT_NFPU_PER_CORE "1" CACHE STRING "Number of FPUs per Spatz")

project(${APP} LANGUAGES C ASM)
include(SnitchUtilities)

add_compile_definitions(__SNRT_USE_PRINT)
add_subdirectory(${SNITCH_SOFTWARE_DIR}/snRuntime snRuntime)
include_directories(${SNRUNTIME_INCLUDE_DIRS})

add_compile_options(-O3 -g -ffunction-sections)

add_executable(${APP} ${PRJ_SRCS})
include_directories(test_data)
include_directories(../../include/)
target_link_libraries(${APP} ${SNITCH_RUNTIME})
target_link_options(${APP} PRIVATE "SHELL:-T ${LINKER_SCRIPT}")
target_compile_definitions(${APP} PUBLIC SNRT_NFPU_PER_CORE=${SNRT_NFPU_PER_CORE})
target_compile_definitions(${APP} PRIVATE SPATZ)
