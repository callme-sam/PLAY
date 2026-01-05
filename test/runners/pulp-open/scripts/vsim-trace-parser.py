import argparse
import os
import re
import sys

SINGLE_CYCLE_FP_OPS = {
    "fadd.", "fsub.", "fmul.", "fdiv.", "fsqrt.",
    "fmin.", "fmax.", "fabs.",
    "fcvt.", "feq.", "flt.", "fle.", "fgt.", "fge.",
    "fsgnj.", "fsgnjn.", "fsgnjx.",
    "fmsub.", "fnmadd.", "fnmsub.", "fmac."
}

DOUBLE_CYCLE_FP_OPS = {
    "fmadd."
}

TRACE_LINE_PATTERN = re.compile(
    r"^\s*\d+ns\s+(\d+)\s+([0-9a-fA-F]+)\s+[0-9a-fA-F]+\s+([a-zA-Z0-9_.]+)"
)

def hex_int(value):
    try:
        return int(value, 16)
    except ValueError:
        raise argparse.ArgumentTypeError(f"'{value}' is not a valid hexadecimal value.")

def parse_args():
    parser = argparse.ArgumentParser(
        description="Parses a QuestaSim Trace file to count the number of FLOPS within a specific address range of instructions."
    )

    parser.add_argument(
        "--file_path",
        type=str,
        required=True,
        help="Path to the input file"
    )

    parser.add_argument(
        "--start",
        type=hex_int,
        help="Starting hexadecimal address (e.g., 0x1000)"
    )

    parser.add_argument(
        "--end",
        type=hex_int,
        help="Ending hexadecimal address (e.g., 0x2000)"
    )

    args = parser.parse_args()
    return args

def get_instruction_flops(mnemonic):
    for op in DOUBLE_CYCLE_FP_OPS:
        if mnemonic.startswith(op):
            return 2
    for op in SINGLE_CYCLE_FP_OPS:
        if mnemonic.startswith(op):
            return 1
    return 0

def parse_trace(file_path, start_pc, end_pc):
    total_flops = 0
    first_cycle = None
    last_cycle = None

    file_path = os.path.abspath(os.path.expanduser(file_path))
    if not os.path.exists(file_path):
        print(f"Error: File {file_path} not found.")
        sys.exit(1)

    with open(file_path, 'r') as f:
        for line in f:
            match = TRACE_LINE_PATTERN.match(line)
            if not match:
                continue

            current_cycle = int(match.group(1))
            current_pc = int(match.group(2), 16)
            mnemonic = match.group(3)

            if start_pc <= current_pc <= end_pc:
                if first_cycle is None:
                    first_cycle = current_cycle
                last_cycle = current_cycle
                total_flops += get_instruction_flops(mnemonic)

    total_cycles = (last_cycle - first_cycle) if first_cycle is not None else 0
    return total_flops, total_cycles

def print_results(flops, cycles):
    print("-" * 30)
    print(f"Total FP ops:  {flops}")
    print(f"Total Cycles: {cycles}")
    print("-" * 30)

def main():
    args = parse_args()

    print(f"Analyzing: {args.file_path}")
    print(f"Range:     [{hex(args.start)} - {hex(args.end)}]")

    flops, cycles = parse_trace(args.file_path, args.start, args.end)

    print_results(flops, cycles)

if __name__ == "__main__":
    main()
