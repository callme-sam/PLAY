# PLAY — Pulp Linear Algebra librarY

A collection of linear algebra kernels optimized for PULP-based architectures. The project aims to be portable, testable, and easy to extend across architectures.

## Table of contents

- [Getting started](#getting-started)
  - [Requirements](#requirements)
  - [PULP-SDK and GVSoC](#pulp-sdk-and-gvsoc)
  - [SPATZ (snrt) quick setup](#spatz)
  - [Python dependencies](#python-dependencies)
- [Repository layout](#repository-layout)
- [Multi-architecture strategy](#multi-architecture-strategy)
  - [Coding pattern](#coding-pattern)
  - [Build-time selection](#build-time-selection)
  - [Centralized internal headers (include/internal)](#centralized-internal-headers-includeinternal)
- [Tests and running](#tests-and-running)
  - [Per-test Makefile flow](#per-test-makefile-flow)
  - [Common Make helpers](#common-make-helpers)
  - [Running examples](#running-examples)
  - [Test flags and options](#test-flags-and-options)
  - [Generating test data](#generating-test-data)
- [Benchmarks](#benchmarks)
- [How to add a new architecture](#how-to-add-a-new-architecture)
- [Roadmap and notes](#roadmap-and-notes)
- [License](#license)
- [Contributors](#contributors)


## Getting started

### Requirements

Testing requires the following components:

- `pulp-sdk`
- `GVSoC` (optional, for simulation)
- `RISC-V GNU Compiler Toolchain`
- `SPATZ` toolchain and `snrt` runtime
- Python 3

### RISC-V GNU Compiler Toolchain

First, install and build the RISC-V toolchain. Follow the instructions [here](https://github.com/pulp-platform/pulp-riscv-gnu-toolchain#risc-v-gnu-compiler-toolchain)

### PULP-SDK and GVSoC

Once the toolchain is ready, install pulp-sdk and build GVSoC. Instructions for obtaining pulp-sdk can be found [here](https://github.com/pulp-platform/pulp-sdk#getting-started), and instructions for building GVSoC are [here](https://github.com/pulp-platform/pulp-sdk#gvsoc).

### SPATZ

Install or build the SPATZ toolchain and `snrt` runtime. Ensure the toolchain `bin` directory is on your `PATH` and CMake can find the compiler. Follow the instruction [here](https://github.com/pulp-platform/spatz)

### Python dependencies

Common Python packages used by generators and helpers:

```bash
pip3 install numpy scipy
```

## Repository layout

- `include/` — Contains the single public header, `play.h`, which exposes the library API.
- `source/` — Contains the implementation of the linear algebra kernels. Each kernel has a top-level `<kernel>.c` and an `arch/` folder with per-arch sources.
- `test/` — Contains test cases for each kernel for each supported architecture. Each kernel under `test/<kernel>/` includes test code, per-target wrappers, and test data.
- `test/common/` — shared test helpers (including `arch_select.mk`).


## Multi-architecture strategy

This project uses a small, consistent pattern to support multiple architectures hiding specific implementation details to the user.

### Coding pattern

For each kernel:

- The public dispatcher lives in `source/<kernel>/<kernel>.c` and forwards to a single unified symbol named `<kernel>_impl` (for example `vector_mul_impl`).
- Each architecture implements that symbol in `source/<kernel>/arch/<kernel>_<arch>.c` (for example `vector_mul_pulp_open.c`, `vector_mul_spatz.c`).

This means the public API and the test-level code do not need to know architecture internals; the build picks the correct arch implementation which provides the unified symbol.

### Build-time selection

- Tests and per-target build wrappers collect top-level kernel sources but intentionally exclude `arch/` files from the wildcard collection.
- `test/common/arch_select.mk` is a centralized Make fragment that maps the `TARGET` make variable to an `ARCH_SUFFIX` (for example `pulp_open` or `spatz`) and provides a macro `add_arch_impl` which appends the chosen `source/<kernel>/arch/<kernel>_$(ARCH_SUFFIX).c` to `APP_SRCS`.
- For SPATZ test flows that use CMake, the test Makefile sets `PRJ_SRCS` to include the chosen arch `.c` so only that file is compiled by the CMake build.

This keeps compilation units minimal (only the needed arch `.c` is built) and avoids duplicate-link conflicts.


### Centralized internal headers (include/internal)

To avoid duplicating small per-kernel header files, this repository uses a centralized internal header directory `include/internal/`.

- `include/internal/arch_interface.h` collects the prototypes for all unified per-kernel implementation symbols (for example `vector_mul_impl`, `vector_sub_impl`, ...).
- Dispatcher files (`source/<kernel>/<kernel>.c`) and arch implementations (`source/<kernel>/arch/<kernel>_<arch>.c`) include the centralized header with:

```c
#include "internal/arch_interface.h"
```

This keeps declarations in a single place and reduces duplication. When you add a new kernel you should:

1. Add the `<kernel>_impl` prototype to `include/internal/arch_interface.h`.
2. Implement the symbol in `source/<kernel>/arch/<kernel>_<arch>.c` for each arch.
3. Update test Makefiles to append the chosen arch implementation (via `test/common/arch_select.mk`).


## Tests and running

This section explains how per-test Makefiles select sources and how to run tests locally.

### Per-test Makefile flow

Typical `test/<kernel>/Makefile` actions:

1. Set `SRC_DIR` and `COMMON_DIR`.
2. Collect top-level kernel sources from `SRC_DIR`, filtering out `SRC_DIR/arch/*`.
3. Include `test/common/arch_select.mk`.
4. Call `$(call add_arch_impl,<kernel>)` to append the selected arch `.c` to `APP_SRCS`.
5. Invoke per-target build rules (pmsis wrappers for PULP or CMake for SPATZ).

### Common Make helpers

- `test/common/arch_select.mk` — centralizes `TARGET` -> `ARCH_SUFFIX` mapping and `add_arch_impl` macro.

### Running examples

Build and run `vector_mul` for PULP_OPEN target:

```bash
cd /path/to/pulp-sdk
source configs/pulp-open.sh
make TARGET=PULP_OPEN -C test/vector_mul clean all run
```

Build and run `vector_mul` for SPATZ (CMake flow):

```bash
export LLVM_PATH="<path/to/spatz-llvm>"
export GVSOC_PATH="<path/to/gvsoc>"
export VLT_PATH="<path/to/verilator/bin>"
export GCC_PATH="<path/to/spatz-riscv-gcc>"
export SPATZ_SW_DIR="<path/to/spatz/sw>"

make TARGET=SPATZ -C test/vector_mul clean all run
```


### Test flags and options

- Common flags to all targets
    - `TARGET=<target>` - Specify the target architecture. Supported targets are `PULP_OPEN` and `SPATZ`
    - `STATS=1` — Collect and print performance counters.
    - `ENABLE_LOGGING=1` — Enable logging.
    - `PRINT_DATA=1` — Print inputs, computed and reference values.

- Flags for `PULP_OPEN`
    - `USE_CLUSTER=1` — Run on the cluster (multi-core) instead of the fabric controller (default).
    - `NUM_CORES=<n>` — Number of cluster cores when `USE_CLUSTER=1` (default `NUM_CORES=1`, max value `NUM_CORES=8`).

- Flags for `SPATZ`
    - `NUM_CC=<n>` - Number of Core-Complexes in Cluster (default `NUM_CC=1`, max value `NUM_CC=2`)
    - `PLATFORM=<platform`> - Emulator platform. Supported platforms are `GVSOC` and `VLT` (default `VLT`)


### Generating test data

Each test case includes a Python script (`generator.py`) to generate input data and expected results. The script typically takes parameters such as vector or matrix dimensions. Data is saved to `data.h`.

To regenerate data:
```bash
$ python3 generator.py <LEN>
```

For example:

```bash
python3 test/vector_mul/generator.py 128
```


## Benchmarks

The **`test_runner.py`** script, located in the `test/runner` directory, automates the execution of all test cases within the main `test` folder.

The script accepts an **optional parameter `--platform`**, which can take the values **`"gvsoc"`** (default value) or **`"rtl"`** to specify the simulation platform.

For each test, the script performs two separate runs: one utilizing a single core on the cluster and a second using eight cores. The results of each run are saved as **`.csv`** files within the platform-specific directory:

* `test/runner/gvsoc/results/` (if `--platform gvsoc` is selected or is the default)
* `test/runner/rtl/results/` (if `--platform rtl` is selected)

Upon completion of all tests, the script processes these data files to generate the **`benchmarks.md`** file, presenting the performance statistics in a comparative table format. This file is saved in the specific platform root directory:

* `test/runner/gvsoc/benchmarks.md`
* `test/runner/rtl/benchmarks.md`


## How to add a new architecture

1. Pick an architecture suffix, e.g. `myarch`.
2. Add `source/<kernel>/arch/<kernel>_myarch.c` and implement `<kernel>_impl(...)`.
3. Update `test/common/arch_select.mk` to map your `TARGET` to `ARCH_SUFFIX`.
4. Implement the test case under directory `test/<kernel>/<new-arch>` (wraps for PULP and/or SPATZ as needed).
5. Add targets or toolchain wrappers in top-level build files if you want convenience aliases (optional).


## Roadmap

- Add support for additional kernels and architectures.


## License


## Contributors
