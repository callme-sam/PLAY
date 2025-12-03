import csv
import os
import re
import json
import glob
from typing import Dict, Any, Optional, Tuple

TRACE_DIR = "traces"
STATS_DIR = "stats"

SINGLE_FP_OPS_PREFIX = (
    # scalar FP
    "fadd.", "fsub.", "fmul.", "fdiv.", "fsqrt.",
    "fmin.", "fmax.", "fabs.",
    "fcvt.", "feq.", "flt.", "fle.", "fgt.", "fge.",
    "fsgnj.", "fsgnjn.", "fsgnjx.",

    # vector FP
    "vfadd.", "vfsub.", "vfmul.", "vfdiv.", "vfsqrt.",
    "vfmin.", "vfmax.", "vfabs.",
    "vfeq.", "vflt.", "vfle.", "vfgt.", "vfge.",
    "vfcvt.", "vfcpk.",
    "vfsgnj.", "vfsgnjn.", "vfsgnjx.",
    "vfrec.", "vfrsqrt."
)

DOUBLE_FP_OPS_PREFIX = (
    "fmadd.", "fmsub.", "fnmadd.", "fnmsub.", "fmac.",
    "vfmadd.", "vfmsub.", "vfnmadd.", "vfnmsub.", "vfmac.",
    "vfdot.", "vfdotp.", "vfdotpr.", "vfavg."
)

TRACE_LINE_PATTERN = re.compile(
    r"^\s*\d+:\s+(\d+):\s+\[[^\]]+\]\s+([^:]+):\d+\s+M\s+[0-9a-fA-F]+\s+([a-zA-Z0-9_.]+)\s+.*$"
)

FILENAME_PATTERN = re.compile(
    r"(.+)_CL_(\d+)\.txt$"
)

DEFAULT_STATS_TEMPLATE = {
    "speedup": None,
    "single_core": {
        "tot_num_inst": None,
        "single_fp": None,
        "double_fp": None,
        "cycles": None,
    },
    "multi_core": {
        "tot_num_inst": None,
        "single_fp": None,
        "double_fp": None,
        "cycles": None,
    }
}


class KernelInfo:
    def __init__(self, name, num_cores):
        self.name = name
        self.cores = num_cores


class Stats:
    def __init__(self, tot_inst, single_fp, double_fp, tot_cycles, speedup):
        self.tot_inst = tot_inst
        self.single_fp = single_fp
        self.double_fp = double_fp
        self.cycles = tot_cycles
        self.speedup = speedup


def get_kernel_info(filename):
    print(f"\nProcessing file {filename}")

    match = re.search(FILENAME_PATTERN, filename)
    if match:
        kernel_name = match.group(1)
        num_cores= int(match.group(2))
        print(f"\tKernel Info: name: {kernel_name} - num cores: {num_cores}")
        return KernelInfo(kernel_name, num_cores)

    return None


def get_start_end_cycles(file_path, kernel_name):
    start_cycles = None
    end_cycles = None

    try:
        with open(file_path, "r") as f:
            for line in f:
                match = TRACE_LINE_PATTERN.search(line)
                if match:
                    cycles = int(match.group(1))
                    func_label = match.group(2)

                    if func_label.startswith(kernel_name):
                        if start_cycles is None:
                            # First occurrence, i.e. start of kernel execution
                            start_cycles = cycles

                        # Update the end cycles with the latest occurrence
                        end_cycles = cycles

    except FileNotFoundError:
        print(f"Error: File not found: {file_path}")
        return None

    if start_cycles is None or end_cycles is None:
        print(f"Warning: Kernel {kernel_name} boundaries not found in {file_path}")
        return None

    print(f"\tKernel Cycles Stats: start={start_cycles} - end={end_cycles}")
    return start_cycles, end_cycles


def count_fp_instructions(file_path, start, end,):
    tot_inst_cnt = 0
    single_fp_cnt = 0
    double_fp_cnt = 0

    try:
        with open(file_path, "r") as f:
            for line in f:
                match = TRACE_LINE_PATTERN.search(line)
                if match:
                    cycles = int(match.group(1))
                    # print(f"\t\tcycles={cycles}")


                    if start <= cycles <= end:
                        instruction = match.group(3)
                        # print(f"\t\tinstruction={instruction}")
                        tot_inst_cnt += 1

                        if instruction.startswith(SINGLE_FP_OPS_PREFIX):
                            single_fp_cnt += 1

                        if instruction.startswith(DOUBLE_FP_OPS_PREFIX):
                            double_fp_cnt += 1

    except Exception as e:
        print(f"Error during instruciton countrig for {file_path}: e")
        return None

    print(f"\tKernel FP Stats: tot={tot_inst_cnt}, single={single_fp_cnt}, double={double_fp_cnt}")
    return tot_inst_cnt, single_fp_cnt, double_fp_cnt

def retrieve_cycles_and_speedup(kernel_name):
    result_dir_path = os.path.join(os.path.dirname(__file__), "..", "gvsoc", "results")
    sc_file_path = os.path.join(result_dir_path, f"{kernel_name}_CL_1.csv")
    mc_file_path = os.path.join(result_dir_path, f"{kernel_name}_CL_8.csv")

    sc_cycles = get_single_core_cycles(sc_file_path)
    mc_cycles = get_multi_core_cycles(mc_file_path)

    if mc_cycles > 0 and sc_cycles is not None:
        return sc_cycles, mc_cycles, (sc_cycles / mc_cycles)
    else:
        return None

def get_kernel_stats(file_path, kernel_info):

    result_cycles = get_start_end_cycles(file_path, kernel_info.name)
    if result_cycles is None:
        print(f"Start and End cycles not found!")
        return None
    start_cycles, end_cycles = result_cycles

    result_fpcount = count_fp_instructions(file_path, start_cycles, end_cycles)
    if result_fpcount is None:
        print(f"FPOS counting failed")
        return None
    tot_inst_cnt, single_fp_cnt, double_fp_cnt = result_fpcount

    result_retrieve = retrieve_cycles_and_speedup(kernel_info.name)
    if result_retrieve is None:
        print(f"Retrieve of cycles failed")

    sc_cycles, mc_cycles, speedup = result_retrieve

    if kernel_info.cores == 1:
        return Stats(tot_inst_cnt, single_fp_cnt, double_fp_cnt, sc_cycles, speedup)
    elif kernel_info.cores == 8:
        return Stats(tot_inst_cnt, single_fp_cnt, double_fp_cnt, mc_cycles, speedup)
    else:
        print(f"Unsupported number of cores")
        return None


def get_current_json_stats(stats_file_path):
    stats = DEFAULT_STATS_TEMPLATE.copy()

    if os.path.exists(stats_file_path):
        try:
            with open(stats_file_path, "r") as f:
                current_stats = json.load(f)
                stats.update(current_stats)
                stats["single_core"].update(current_stats.get("single_core", {}))
                stats["multi_core"].update(current_stats.get("multi_core", {}))
        except json.JSONDecodeError:
            print(f"Warning: Corrupted JSON file {stats_file_path}. Rewriting it.")
        except Exception as e:
            print(f"Error reading {stats_file_path}: {e}")

    return stats


def get_single_core_cycles(sc_file_path):
    sc_cycles = 0.0

    try:
        with open(sc_file_path, mode="r", newline="") as file:
            reader = csv.DictReader(file)
            try:
                row = next(reader)
                sc_cycles = float(row["cycles"])
            except StopIteration:
                print(f"Error: single-core file {sc_file_path} is empty or header-only")
                return None
    except FileNotFoundError:
        print(f"Error: single-core file not fount at {sc_file_path}")
        return None
    except KeyError:
        print(f"Error: 'cycles' column not found in {sc_file_path}")
        return None

    return sc_cycles

def get_multi_core_cycles(mc_file_path):
    mc_cycles = 0.0

    try:
        with open(mc_file_path, mode="r", newline="") as file:
            reader = csv.DictReader(file)
            found_data = False
            for row in reader:
                found_data = True
                try:
                    current_cycles = float(row["cycles"])
                    if current_cycles > mc_cycles:
                        mc_cycles = current_cycles
                except ValueError:
                    print(f"Warning: Non-numeric 'cycles' value found in {mc_file_path}. Skipping row")
                    continue

            if not found_data:
                print(f"Error: multi-core file {mc_file_path} is empty or header-only.")
                return mc_cycles

    except FileNotFoundError:
        print(f"Error: multi-core file not found at {mc_file_path}")
        return mc_cycles
    except KeyError:
        print(f"Error: 'cycles' column not found in {mc_file_path}")
        return mc_cycles

    return mc_cycles

def update_json_stats(json_stats, kernel_stats, kernel_info):
    if kernel_info.cores == 1:
        target_section = json_stats["single_core"]
    elif kernel_info.cores == 8:
        target_section = json_stats["multi_core"]
    else:
        print(f"Error: Number of cores ({kernel_info.cores}) not supported for kernel {kernel_info.name}.")
        return None

    target_section["tot_num_inst"] = kernel_stats.tot_inst
    target_section["single_fp"] = kernel_stats.single_fp
    target_section["double_fp"] = kernel_stats.double_fp
    target_section["cycles"] = kernel_stats.cycles

    json_stats["speedup"] = kernel_stats.speedup

    return json_stats


def write_stats(kernel_info, kernel_stats):
    os.makedirs(STATS_DIR, exist_ok=True)

    stats_file_name = f"{kernel_info.name}_stats.json"
    stats_file_path = os.path.join(STATS_DIR, stats_file_name)

    json_stats = get_current_json_stats(stats_file_path)
    json_stats = update_json_stats(json_stats, kernel_stats, kernel_info)

    try:
        with open(stats_file_path, "w") as f:
            json.dump(json_stats, f, indent=4)
        print(f"Updates of {stats_file_path} success\n")
    except Exception as e:
        print(f"Error writing to {stats_file_path}: {e}")


def main():
    trace_files = glob.glob(os.path.join(TRACE_DIR, "*_CL_*.txt"))
    trace_files.sort()
    for file_path in trace_files:
        filename = os.path.basename(file_path)
        kernel_info = get_kernel_info(filename)
        kernel_stats = get_kernel_stats(file_path, kernel_info)
        write_stats(kernel_info, kernel_stats)

    print(f"\n--- All traces has been parsed ---\n")


if __name__ == "__main__":
    main()
