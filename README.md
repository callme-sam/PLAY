# PLAY -- Pulp Linear Algebra librarY

A collection of linear algebra kernels optimized for PULP-based architectures.

Currently, development and testing are focused on the PULP CLUSTER platform. The project aims to provide efficient, scalable, and portable building blocks for vector and matrix operations, targeting embedded and parallel RISC-V systems.

## Getting Started

Testing requires the following components:
- pulp-sdk
- GVSoC
- RISC-V GNU Compiler Toolchain

### RISC-V GNU Compiler Toolchain

First, install and build the RISC-V toolchain. Follow the instructions [here](https://github.com/pulp-platform/pulp-riscv-gnu-toolchain#risc-v-gnu-compiler-toolchain).

### PULP-SDK

Once the toolchain is ready, install pulp-sdk and build GVSoC. Instructions for obtaining pulp-sdk can be found [here](https://github.com/pulp-platform/pulp-sdk#getting-started), and instructions for building GVSoC are [here](https://github.com/pulp-platform/pulp-sdk#gvsoc).

### Python

Each test case includes a `generator.py` script that generates input data and expected results for verification. The following Python dependencies are required (add any others as needed):

- `numpy`
- `scipy`

Install them with:
```bash
pip install numpy scipy
```

## Repository Organization

- `include/`: Contains the single public header, `play.h`, which exposes the library API.
- `source/`: Contains the implementation of the linear algebra kernels. Each subdirectory corresponds to a specific kernel implementation. Each implementation includes a serial and a parallel version.
- `test/`: Contains test cases for each kernel. Each subdirectory corresponds to a specific kernel and includes a Makefile, test code, and data generation scripts.
- `test/<kernel>/test_data/`: Stores generated input data and reference results for each test case.

## Usage

To use the library, include the `play.h` header from the `include` directory in your project, and add the relevant source files from the `source` directory to your build system.

Example:
```c
#include "play.h"
```
Make sure to configure your build system to include the `include` directory in the header search path and compile the required source files.

## Tests

Each kernel has an associated test case in the `test` directory.

To run a test, first source the configuration script for your target platform:
```bash
$ cd pulp-sdk
$ source configs/pulp-open.sh
```
Then, enter the test directory and run:
```bash
$ cd test/<test-dir>
$ make clean all run
```

You can pass several flags to `make`:
- `USE_CLUSTER=1` — Run the test on the Cluster. If not specified, the test runs on the Fabric Controller (default: `USE_CLUSTER` not set).
- `NUM_CORES=8` — If `USE_CLUSTER` is set, specifies the number of cluster cores (default: `NUM_CORES=1`).
- `STATS=1` — Enable collection and prints of various performance counters.
- `ENABLE_LOGGING=1` - Enable logs
- `PRINT_DATA=1` — Print input data, computed values, and reference values to stdout.

### Generating Input Data and Reference Values

Each test case includes a Python script (`generator.py`) to generate input data and expected results. The script typically takes parameters such as vector or matrix dimensions. Data is saved to `data.h`.

To regenerate data:
```bash
$ python3 generator.py <LEN>
```

### Benchmarks

The `runner.py` script, located in the `test/runner` directory, automates the execution of all test cases within the main `test` folder. For each test, it performs two separate runs: one utilizing a single core on the cluster and a second using eight cores. The results of each run are saved as a `.csv` file in the `test/runner/results` directory. Upon completion of all tests, the script processes these data files to generate the [benchmarks.md](test/runner/benchmarks.md) file, presenting the performance statistics in a comparative table format.


## Roadmap

- Add support for additional kernels and architectures.

## License


## Contributors
