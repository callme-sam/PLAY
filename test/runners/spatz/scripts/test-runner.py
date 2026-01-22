import argparse
import subprocess
import re
import csv
import os

from types import SimpleNamespace


def parse_args():
    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--platform",
        type=str,
        choices=["gvsoc", "vsim", "vlt"],
        required=False,
        default="gvsoc",
    )

    args = parser.parse_args()
    return args


def set_paths(args):
    paths = SimpleNamespace()

    paths.script_dir = os.path.dirname(os.path.abspath(__file__))
    paths.project_root = os.path.abspath(os.path.join(paths.script_dir, "../../../../"))
    paths.runners_dir = os.path.abspath(os.path.join(paths.script_dir, "../../"))
    paths.test_root = os.path.join(paths.project_root, "test")
    paths.benchmarks_dir = os.path.join(paths.runners_dir, "spatz/benchmarks")
    paths.platform_dir = os.path.join(paths.benchmarks_dir, f"{args.platform}")
    paths.results_dir = os.path.join(paths.platform_dir, "results")

    os.makedirs(paths.results_dir, exist_ok=True)
    return paths


def set_test_dirs(paths):
    test_directories = [
        d for d in os.listdir(paths.test_root)
        if os.path.isdir(os.path.join(paths.test_root, d))
        and not d.startswith('_')
        and d not in ["common", "runners", "hello"]
    ]
    test_directories.sort()
    return test_directories


def parse_and_save_stats(paths, test_dir_name, output):
    start_info_line = "Printing statistics:"
    if start_info_line not in output:
        print(f"Warning: Could not find statistics for test {test_dir_name}.")
        return False

    stats_start_index = output.find(start_info_line)
    stats_block = output[stats_start_index:]

    match = re.search(r"\[0\]\s*cycles:\s*([\d.eE+-]+)", stats_block)
    if not match:
        print(f"Warning: Could not find cycles for test {test_dir_name}.")
        return False

    cycles = match.group(1)

    csv_filename = os.path.join(paths.results_dir, f"{test_dir_name}_SPATZ.csv")

    with open(csv_filename, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile, lineterminator='\n')
        writer.writerow(['cycles'])
        writer.writerow([cycles])

    print(f"Statistics data saved to {csv_filename}")
    return True

import os
import csv

def generate_markdown_report(platform_dir, results_dir):
    print("\n--- Generating Markdown Report ---")

    dimensions = {
        'linalg_cholesky_decomp': '64x64',
        'linalg_gemv': '64x32',
        'linalg_gemv_trans': '64x32',
        'linalg_lu_decomp': '64x32',
        'linalg_lu_solve': '64x64',
        'linalg_svd': '64x32',
        'linalg_svd_jacobi': '64x64',
        'linalg_svd_lsv': '64x32',
        'matrix_memcpy': '64x32',
        'matrix_mul': '64x32 <br> 32x64',
        'matrix_mul_trans_A': '64x32 <br> 48x32',
        'matrix_mul_trans_B': '32x64 <br> 32x48',
        'matrix_set_all': '64x32',
        'matrix_swap_rows': '16x256',
        'matrix_trans': '64x32',
        'vector_add': '2048',
        'vector_axpy': '2048',
        'vector_dot': '2048',
        'vector_memcpy': '2048',
        'vector_min': '2048',
        'vector_mul': '2048',
        'vector_offset': '2048',
        'vector_scale': '2048',
        'vector_set_all': '2048',
        'vector_sub': '2048',
    }

    markdown_content = []

    for filename in sorted(os.listdir(results_dir)):
        if filename.endswith('_SPATZ.csv'):
            test_name = filename.replace('_SPATZ.csv', '')
            file_path = os.path.join(results_dir, filename)
            with open(file_path, 'r') as csvfile:
                reader = csv.DictReader(csvfile)
                rows = list(reader)
                if not rows:
                    continue

                cycles = rows[0].get('cycles', '')

                markdown_content.append(f"## {test_name.replace('_', ' ').upper()}")
                markdown_content.append("")
                markdown_content.append("| Problem size | Cycles |")
                markdown_content.append("|-|-|")
                markdown_content.append(f"| {dimensions.get(test_name, '')} | {cycles} |")
                markdown_content.append("")

    markdown_filename = os.path.join(platform_dir, "benchmarks.md")
    with open(markdown_filename, 'w') as mdfile:
        mdfile.write("\n".join(markdown_content))

    print(f"Markdown Report saved to {markdown_filename}")


def run_test_case(args, paths, test_dir_name):
    current_test_dir = os.path.join(paths.test_root, test_dir_name)

    make_command = f"make clean all run STATS=1 TARGET=SPATZ PLATFORM={args.platform.upper()}"

    print(f"\n--- Running {test_dir_name} on Spatz ---")
    print(f"Command: cd {current_test_dir} && {make_command}")

    try:
        proc = subprocess.Popen(
            make_command,
            shell=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            universal_newlines=True,
            cwd=current_test_dir
        )

        output_lines = []
        for line in proc.stdout:
            print(line, end='')
            output_lines.append(line)

        proc.wait()
        result_stdout = ''.join(output_lines)

        parse_and_save_stats(paths, test_dir_name, result_stdout)
    except subprocess.CalledProcessError as e:
        print(f"Error during compilation or execution for {test_dir_name}")
        print(f"STDOUT:\n{e.stdout}")
        print(f"STDERR:\n{e.stderr}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")


def main():
    args = parse_args()
    paths = set_paths(args)
    test_dirs = set_test_dirs(paths)

    for test_dir_name in test_dirs:
        run_test_case(args, paths, test_dir_name)

    generate_markdown_report(paths.platform_dir, paths.results_dir)

    print("\nAll tests and report generation have been compelted.")


if __name__ == "__main__":
    main()
