import argparse
import os
import re
import subprocess
from types import SimpleNamespace

def parse_args():
    parser = argparse.ArgumentParser(
        description="Script for generating traces."
    )

    parser.add_argument(
        "--platform",
        type=str,
        choices=["gvsoc", "rtl"],
        required=False,
        default="gvsoc",
        help="Specifies the execution platform. Allowed values: 'gvsoc' or 'rtl'. Default is 'gvsoc'."
    )

    args = parser.parse_args()
    return args

def set_paths(args):
    paths = SimpleNamespace()

    paths.script_dir = os.path.dirname(os.path.abspath(__file__))
    paths.project_root = os.path.abspath(os.path.join(paths.script_dir, "../../../../"))
    paths.runners_dir = os.path.abspath(os.path.join(paths.script_dir, "../../"))
    paths.test_root = os.path.join(paths.project_root, "test")
    paths.traces_dir = os.path.join(paths.runners_dir, "pulp-open/traces")
    paths.traces_dir = os.path.join(paths.traces_dir, f"{args.platform}")

    os.makedirs(paths.traces_dir, exist_ok=True)
    return paths

def set_trace_dirs(paths):
    trace_dirs = [
        d for d in os.listdir(paths.test_root)
        if os.path.isdir(os.path.join(paths.test_root, d))
        and not d.startswith('_')
        and d not in ["common", "runners", "hello"]
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

def generate_trace(args, paths, trace_dir_name, num_cores):
    current_trace_dir = os.path.join(paths.test_root, trace_dir_name)
    trace_filename = os.path.join(paths.traces_dir, f"{trace_dir_name}_CL_{num_cores}.txt")
    make_cmd = f"make clean all run USE_CLUSTER=1 NUM_CORES={num_cores} TARGET=PULP_OPEN platform={args.platform} runner_args=\"--trace=insn:{trace_filename}\""

    print(f"\n--- Running {trace_dir_name} with {num_cores} core ---")
    print(f"--- Command: cd {current_trace_dir} && {make_cmd} ---")

    try:
        subprocess.run(make_cmd, shell=True, capture_output=False, text=True, check=True, cwd=current_trace_dir)
        remove_ansi(trace_filename)

    except subprocess.CalledProcessError as e:
        print(f"Error during compilation or execution for {trace_dir_name} (cores={num_cores}):")
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
    args = parse_args()
    paths = set_paths(args)
    trace_dirs = set_trace_dirs(paths)

    for trace_dir_name in trace_dirs:
        generate_trace(args, paths, trace_dir_name, 1)
        generate_trace(args, paths, trace_dir_name, 8)

    remove_debug_info(paths)

    print("\n--- All traces have been generated. ---")

if __name__ == "__main__":
    main()
