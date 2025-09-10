# Vector Subtraction Test on PULP Cluster

This folder contains the `vector_sub` test for the PULP Cluster, with various configurations to evaluate performance under different loop types and optimizations.

## Usage

To run the test, use the `make` command with the appropriate flags to specify the desired configuration.

### Flags

| Flag              | Description                                                          | Values     |
|-------------------|----------------------------------------------------------------------|------------|
| `FOR`             | Use a `for` loop.                                                    | `1` or `0` |
| `WHILE`           | Use a `so-while` loop.                                               | `1` or `0` |
| `INTERLEAVE`      | Enable loop interleaving optimization.                               | `1` or `0` |
| `UNROLL`          | Enable loop unrolling optimization.                                  | `1` or `0` |
| `BOTH`            | Enable both loop interleaving and unrolling.                         | `1` or `0` |
| `NUM_CORES`       | Number of cores to use for execution.                                | `1` or `8` |
| `STATS`           | Print performance statistics from hardware counters.                 | `1` or `0` |
| `USE_CLUSTER`     | Run the test on the cluster instead of the Fabric Controller.        | `1` or `0` |
| `PRINT_DATA`      | Print input data, results, and reference values.                     | `1` or `0` |

### Examples

**1. Run with a standard `for` loop on cluter with 8 cores and print statistics:**
```sh
make clean all run STATS=1 USE_CLUSTER=1 NUM_CORES=8 FOR=1
```

**2. Run with a `do-while` loop on cluter with 8 cores, whit unrolling optimizatino and print statistics:**
```sh
make clean all run STATS=1 USE_CLUSTER=1 NUM_CORES=8 WHILE=1 UNROLL=1
```
