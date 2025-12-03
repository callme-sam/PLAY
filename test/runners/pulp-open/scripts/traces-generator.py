import os
import re
import subprocess
from types import SimpleNamespace

def set_paths():
    paths = SimpleNamespace()

    paths.script_dir = os.path.dirname(os.path.abspath(__file__))
    paths.project_root = os.path.abspath(os.path.join(paths.script_dir, "../../.."))
    paths.test_root = os.path.join(paths.project_root, "test")
    paths.traces_dir = os.path.join(paths.script_dir, "traces")

    os.makedirs(paths.traces_dir, exist_ok=True)
    return paths

def set_trace_dirs(paths):
    trace_dirs = [
        d for d in os.listdir(paths.test_root)
        if os.path.isdir(os.path.join(paths.test_root, d))
        and d in ["vector_mul", "matrix_mul", "linalg_svd", "linalg_svd_jacobi", "linalg_svd_lsv", "linalg_lu_solve",
                  "linalg_lu_decomp", "linalg_gemv", "linalg_cholesky_decomp"]
        # and d not in ["common", "runner", "hello"]
    ]
    trace_dirs.sort()
    return trace_dirs

def remove_ansi(filename):
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')

    try:
        with open(filename, 'r', encoding='utf-8') as f:
            content = f.read()

        cleaned_content = ansi_escape.sub('', content)

        with open(filename, 'w', encoding='utf-8') as f:
            f.write(cleaned_content)

        print(f"--- ANSI characters removed ---")

    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

def generate_trace(paths, trace_dir_name, num_cores):
    current_trace_dir = os.path.join(paths.test_root, trace_dir_name)
    trace_filename = os.path.join(paths.traces_dir, f"{trace_dir_name}_CL_{num_cores}.txt")
    make_cmd = f"make clean all run USE_CLUSTER=1 NUM_CORES={num_cores} runner_args=\"--trace=insn:{trace_filename}\""

    print(f"\n--- Running {trace_dir_name} with {num_cores} core ---")
    print(f"--- Command: cd {current_trace_dir} && {make_cmd} ---")

    try:
        subprocess.run(make_cmd, shell=True, capture_output=False, text=True, check=True, cwd=current_trace_dir)
        remove_ansi(trace_filename)

    except subprocess.CalledProcessError as e:
        print(f"Error during compilation or execution for {test_dir_name} (cores={num_cores}):")
        print(f"STDOUT:\n{e.stdout}")
        print(f"STDERR:\n{e.stderr}")

    except Exception as e:
        print(f"An unexpected error occurred: {e}")

def remove_debug_info(paths):
    rm_cmd = f"find {paths.project_root} -name \"*.debugInfo\" -type f -delete"

    print(f"\n--- Cleaning .debugInfo files ---\n")
    try:
        subprocess.run(rm_cmd, shell=True, capture_output=False, text=True, check=True, cwd=paths.project_root)

    except subprocess.CalledProcessError as e:
        print(f"Error during .debugInfo cleanup")
        print(f"STDOUT:\n{e.stdout}")
        print(f"STDERR:\n{e.stderr}")

    except Exception as e:
        print(f"An unexpected error occurred: {e}")



def main():
    paths = set_paths()
    trace_dirs = set_trace_dirs(paths)

    for trace_dir_name in trace_dirs:
        generate_trace(paths, trace_dir_name, 1)
        generate_trace(paths, trace_dir_name, 8)

    remove_debug_info(paths)

    print("\n--- All traces have been generated. ---")

if __name__ == "__main__":
    main()
