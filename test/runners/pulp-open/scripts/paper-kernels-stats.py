import subprocess

KERNELS = [
    "linalg_cholesky_decomp",
    "linalg_gemv",
    "linalg_lu_decomp",
    "linalg_lu_solve",
    "linalg_svd"
]

CORES = [1, 8]

LOG_FILE = "pulp_open_rtl.log"

def run_make(kernel, num_cores, log_file_handle):
    cmd = f"make -C test/{kernel}/ clean all run TARGET=PULP_OPEN STATS=1 USE_CLUSTER=1 NUM_CORES={num_cores} platform=rtl"
    print(f"\n--- Running {kernel} with {num_cores} cores ---")
    print(f"Command: {cmd}\n")

    proc = subprocess.Popen(
        cmd,
        shell=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True
    )

    for line in proc.stdout:
        print(line, end='')
        log_file_handle.write(line)

    proc.wait()

def main():
    with open(LOG_FILE, 'w') as log_file:
        for kernel in KERNELS:
            for num_cores in CORES:
                run_make(kernel, num_cores, log_file)

    print(f"\nAll runs completed. Output saved to {LOG_FILE}")

if __name__ == "__main__":
    main()
