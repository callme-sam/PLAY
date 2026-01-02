import subprocess

KERNELS = [
    "linalg_cholesky_decomp",
    "linalg_gemv",
    "linalg_lu_decomp",
    "linalg_lu_solve",
    "linalg_svd"
]

LOG_FILE = "spatz_vsim.log"

def run_make(kernel, log_file_handle):
    cmd = f"make -C test/{kernel} clean all run TARGET=SPATZ PLATFORM=VSIM STATS=1"
    print(f"\n--- Running {kernel} ---")
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
            run_make(kernel, log_file)

    print(f"\nAll runs completed. Output saved to {LOG_FILE}")

if __name__ == "__main__":
    main()
