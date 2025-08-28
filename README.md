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
- `STATS=1` — Enable collection of various statistics.
- `PRINT_DATA=1` — Print input data, computed values, and reference values to stdout.

### Generating Input Data and Reference Values

Each test case includes a Python script (`generator.py`) to generate input data and expected results. The script typically takes parameters such as vector or matrix dimensions. Data is saved to `data.h`.

To regenerate data:
```bash
$ python3 generator.py <LEN>
```

## Benchmarks

| Kernel              | #Cores   | Dim.      | Cycles | Instr. | ld-stall | I-miss | CPI |
|---------------------|----------|-----------|--------|--------|---------|-------|-----|
| matrix_memcpy       | 1        | 64x32     | 13035  | 8793   | 1       | 5     | 1.48|
| matrix_memcpy       | 8        | 64x32     | 1719   | 1127   | 1       | 5     | 1.53|
| matrix_mul          | 1        | 64x32 <br> 32x64| 963446 | 696862 | 0       | 14    | 1.38|
| matrix_mul          | 8        | 64x32 <br> 32x64| 120209 | 87140  | 0       | 13    | 1.38|
| matrix_mul_trans    | 1        | 64x32 <br> 32x48| 728753 | 522847 | 0       | 8     | 1.39|
| matrix_mul_trans    | 8        | 64x32 <br> 32x48| 91267  | 65389  | 0       | 6     | 1.40|
| matrix_set_all      | 1        | 64x32     | 11040  | 6676   | 0       | 4     | 1.65|
| matrix_set_all      | 8        | 64x32     | 1474   | 858    | 0       | 4     | 1.72|
| matrix_trans        | 1        | 64x32     | 13089  | 8852   | 0       | 2     | 1.48|
| matrix_trans        | 8        | 64x32     | 1760   | 1130   | 0       | 4     | 1.56|
| vector_add          | 1        | 2048      | 20517  | 14362  | 1       | 2     | 1.43|
| vector_add          | 8        | 2048      | 2641   | 1824   | 0       | 4     | 1.45|
| vector_axpy         | 1        | 2048      | 20521  | 14365  | 1       | 3     | 1.43|
| vector_axpy         | 8        | 2048      | 2642   | 1827   | 0       | 2     | 1.45|
| vector_dot          | 1        | 2048      | 22591  | 16424  | 0       | 6     | 1.38|
| vector_dot          | 8        | 2048      | 3026   | 2089   | 8       | 9     | 1.45|
| vector_memcpy       | 1        | 2048      | 16420  | 10263  | 1       | 4     | 1.60|
| vector_memcpy       | 8        | 2048      | 2127   | 1309   | 0       | 5     | 1.63|
| vector_min          | 1        | 2048      | 26658  | 14372  | 2049    | 4     | 1.85|
| vector_min          | 8        | 2048      | 3452   | 1828   | 255     | 6     | 1.89|
| vector_mul          | 1        | 2048      | 20517  | 14362  | 1       | 2     | 1.43|
| vector_mul          | 8        | 2048      | 2641   | 1824   | 0       | 4     | 1.45|
| vector_offset       | 1        | 2048      | 18466  | 12313  | 1       | 0     | 1.50|
| vector_offset       | 8        | 2048      | 2401   | 1567   | 0       | 2     | 1.53|
| vector_scale        | 1        | 2048      | 18466  | 12313  | 1       | 0     | 1.50|
| vector_scale        | 8        | 2048      | 2401   | 1567   | 0       | 2     | 1.53|
| vector_sub          | 1        | 2048      | 20517  | 14362  | 1       | 2     | 1.43|
| vector_sub          | 8        | 2048      | 2641   | 1824   | 0       | 4     | 1.45|


## Speedup and Efficiency Comparison

| Kernel           | Speedup | Efficiency |
|------------------|---------|------------|
| matrix_memcpy    | 7.59    | 0.95       |
| matrix_mul       | 7.99    | 1.00       |
| matrix_mul_trans | 7.99    | 1.00       |
| matrix_set_all   | 7.49    | 0.94       |
| matrix_trans     | 7.44    | 0.93       |
| vector_add       | 7.77    | 0.97       |
| vector_axpy      | 7.77    | 0.97       |
| vector_dot       | 7.47    | 0.93       |
| vector_memcpy    | 7.72    | 0.97       |
| vector_min       | 7.72    | 0.97       |
| vector_mul       | 7.77    | 0.97       |
| vector_offset    | 7.69    | 0.96       |
| vector_scale     | 7.69    | 0.96       |
| vector_sub       | 7.77    | 0.97       |


## Roadmap

- Add support for additional kernels and architectures.

## License


## Contributors
