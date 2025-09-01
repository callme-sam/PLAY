import subprocess
import re
import csv
import os
import sys

# Determine key paths based on the script's location
script_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(script_dir, "../../"))
test_root = os.path.join(project_root, "test")
results_dir = os.path.join(script_dir, "results")

# Ensure the results directory exists
os.makedirs(results_dir, exist_ok=True)

def parse_and_save_stats(test_dir_name, num_cores, output):
    """
    Parses the raw terminal output, extracts statistics, and saves them to a CSV file.
    """
    # 1. Find the correct statistics block in the output
    start_info_line = f"Printing statistics:"
    if start_info_line not in output:
        print(f"Warning: Could not find the header for test {test_dir_name} ({num_cores} cores).")
        return False

    stats_start_index = output.find(start_info_line)
    stats_block = output[stats_start_index:]

    # 2. Initialize the data structure for all cores
    all_cores_data = {core_id: {} for core_id in range(num_cores)}

    # 3. Define the regular expression for each statistics line
    # Format: [core_id] <statistic_name>: <value>
    pattern = re.compile(r"\[(\d+)\]\s+([\w\s]+):\s+([\d.]+)")

    # 4. Populate the data structure
    for line in stats_block.splitlines():
        match = pattern.search(line)
        if match:
            core_id = int(match.group(1))
            key = match.group(2).strip().replace(" ", "_")
            value = match.group(3)
            all_cores_data[core_id][key] = value

    # 5. Get the headers from the first core's data
    fieldnames = list(all_cores_data[0].keys()) if all_cores_data[0] else []
    fieldnames.insert(0, 'id')

    # 6. Write the data to the CSV file
    csv_filename = os.path.join(results_dir, f"{test_dir_name}_CL_{num_cores}.csv")

    with open(csv_filename, 'w', newline='') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, lineterminator='\n')
        writer.writeheader()

        for core_id in range(num_cores):
            row_data = all_cores_data[core_id]
            row_to_write = {field: row_data.get(field, '') for field in fieldnames}
            row_to_write['id'] = core_id
            writer.writerow(row_to_write)

    print(f"Statistics data saved to {csv_filename}")
    return True

def run_test_case(test_dir_name, num_cores):
    """
    Executes the 'make' command to run test.
    """
    current_test_dir = os.path.join(test_root, test_dir_name)

    make_command = f"make clean all run STATS=1 USE_CLUSTER=1 NUM_CORES={num_cores}"

    print(f"\n--- Running {test_dir_name} with {num_cores} cores ---")
    print(f"Command: cd {current_test_dir} && {make_command}")

    try:
        result = subprocess.run(make_command, shell=True, capture_output=True, text=True, check=True, cwd=current_test_dir)
        parse_and_save_stats(test_dir_name, num_cores, result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Error during compilation or execution for {test_dir_name} (cores={num_cores}):")
        print(f"STDOUT:\n{e.stdout}")
        print(f"STDERR:\n{e.stderr}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")


def generate_markdown_report(results_dir):
    """
    Reads CSV files and generates a Markdown file with a separate table for each kernel.
    """
    print("\n--- Generating Markdown Report ---")

    dimensions = {
        'linalg_gemv': '2048',
        'matrix_memcpy': '64x32',
        'matrix_mul': '64x32 <br> 32x64',
        'matrix_mul_trans': '64x32 <br> 32x48',
        'matrix_set_all': '64x32',
        'matrix_swap_rows': '4x256',
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

    test_data = {}

    for filename in os.listdir(results_dir):
        if filename.endswith('.csv'):
            file_path = os.path.join(results_dir, filename)
            parts = filename.split('_CL_')
            test_name = parts[0]
            cores = int(parts[1].replace('.csv', ''))

            with open(file_path, 'r') as csvfile:
                reader = csv.DictReader(csvfile)

                if test_name not in test_data:
                    test_data[test_name] = {'headers': reader.fieldnames, 1: [], 8: []}

                if cores == 1:
                    test_data[test_name][1] = list(reader)
                elif cores == 8:
                    test_data[test_name][8] = list(reader)

    markdown_content = []
    sorted_test_names = sorted(test_data.keys())

    for test_name in sorted_test_names:
        data_1_core = test_data[test_name][1]
        data_8_cores = test_data[test_name][8]
        headers = test_data[test_name]['headers']

        if not data_1_core or not data_8_cores:
            print(f"Skipping {test_name}: missing data for 1 or 8 cores.")
            continue

        # Start a new table for the kernel
        markdown_content.append(f"## {test_name.replace('_', ' ').upper()}")
        markdown_content.append("")

        # Determine table headers dynamically
        display_headers = ['Core', 'Problem Dimension'] + [h.replace('_', ' ') for h in headers if h != 'id']
        markdown_content.append("| " + " | ".join(display_headers) + " |")
        markdown_content.append("|-" + "|-".join(["" for _ in display_headers]) + "|")

        # Add 1-core row
        markdown_content.append("**Single-core Execution**")
        row_1_data = data_1_core[0]
        row_values = ['0']
        row_values.append(dimensions.get(test_name, ''))
        for header in headers:
            if header != 'id':
                row_values.append(row_1_data.get(header, ''))
        markdown_content.append("| " + " | ".join(row_values) + " |")

        # Add separator line
        # markdown_content.append("")
        markdown_content.append("**Multi-core Execution**")

        # Add 8-cores rows
        max_cycles_8_cores = 0
        for row_8_data in data_8_cores:
            row_values = [row_8_data.get('id', '')]
            row_values.append(dimensions.get(test_name, ''))

            # Find the max cycles for speedup calculation
            current_cycles = float(row_8_data.get('cycles', 0))
            if current_cycles > max_cycles_8_cores:
                max_cycles_8_cores = current_cycles

            for header in headers:
                if header != 'id':
                    row_values.append(row_8_data.get(header, ''))
            markdown_content.append("| " + " | ".join(row_values) + " |")

        # Add speedup row
        cycles_1 = float(row_1_data.get('cycles', 0))
        speedup = cycles_1 / max_cycles_8_cores if max_cycles_8_cores > 0 else 0

        speedup_row_values = ['**Speedup**', f"**{speedup:.2f}**"] + [''] * (len(display_headers) - 2)
        markdown_content.append("| " + " | ".join(speedup_row_values) + " |")
        markdown_content.append("") # Empty line to separate tables

    # Save to file
    markdown_filename = os.path.join(script_dir, "benchmarks.md")
    with open(markdown_filename, 'w') as mdfile:
        mdfile.write("\n".join(markdown_content))

    print(f"Markdown Report saved to {markdown_filename}")

def main():

    test_directories = [
        d for d in os.listdir(test_root)
        if os.path.isdir(os.path.join(test_root, d))
        and d not in ["common", "runner"]
    ]
    test_directories.sort()

    for test_dir_name in test_directories:
        run_test_case(test_dir_name, 1)
        run_test_case(test_dir_name, 8)

    # Generate the Markdown report after all tests have been executed
    generate_markdown_report(results_dir)

    print("\nAll tests and the report generation have been completed.")

if __name__ == "__main__":
    main()
