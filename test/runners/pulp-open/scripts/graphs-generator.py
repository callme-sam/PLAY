import argparse
import os
import json
import matplotlib.pyplot as plt
import numpy as np

from types import SimpleNamespace
from typing import Dict, Any, List, Tuple

FREQUENCY_MHZ = 500
FREQUENCY_HZ = FREQUENCY_MHZ * 1_000_000

def parse_args():
    parser = argparse.ArgumentParser(
        description="Script for generating graphs"
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
    paths.benchmarks_dir = os.path.join(paths.runners_dir, "pulp-open/benchmarks")
    paths.platform_dir = os.path.join(paths.benchmarks_dir, f"{args.platform}")
    paths.results_dir = os.path.join(paths.platform_dir, "results")
    paths.graphs_dir = os.path.join(paths.runners_dir, "pulp-open/graphs")
    paths.graphs_dir = os.path.join(paths.graphs_dir, f"{args.platform}")
    paths.stats_dir = os.path.join(paths.runners_dir, "pulp-open/stats")
    paths.stats_dir = os.path.join(paths.stats_dir, f"{args.platform}")

    os.makedirs(paths.graphs_dir, exist_ok=True)
    os.makedirs(paths.stats_dir, exist_ok=True)

    return paths

def load_stats(paths):
    stats = {}
    for filename in os.listdir(paths.stats_dir):
        kernel_name = filename.replace("_stats.json", "")
        file_path = os.path.join(paths.stats_dir, filename)
        try:
            with open(file_path, "r") as f:
                stats[kernel_name] = json.load(f)

        except json.JSONDecodeError as e:
            print(f"Error decodiing JSON in file {file_path}: {e}")
        except Exception as e:
            print(f"An unexpected error occured while reading file {file_path}")
    return stats

def compute_gflops(data):
    sc_data = data.get("single_core", {})
    mc_data = data.get("multi_core", {})

    def _gflops_for_mode(mode_data):
        single_fp = mode_data.get("single_fp", 0)
        double_fp = mode_data.get("double_fp", 0)
        execution_cycles = mode_data.get("cycles", 0)

        total_fp_inst = single_fp + (double_fp * 2)

        if execution_cycles > 0:
            execution_time_sec = execution_cycles / FREQUENCY_HZ
            gflops = (total_fp_inst / execution_time_sec) / 1_000_000_000
            return gflops
        else:
            return 0.0

    sc_gflops = _gflops_for_mode(sc_data)
    mc_gflops = _gflops_for_mode(mc_data)

    return sc_gflops, mc_gflops

def generate_speedup_bar_chart(paths, stats):
    kernel_names = list(stats.keys())
    kernel_names.sort()

    speedups = [stats[name].get("speedup", 0.0) for name in kernel_names]
    kernel_labels = [name.replace("_", " ") for name in kernel_names]

    fig, ax = plt.subplots(figsize=(12, 6))
    bar_width = 0.8
    x_pos = np.arange(len(kernel_names)) * 2.0 # 2.0 is the center position step (bar_width + space_between_groups)
    bars = ax.bar(x_pos, speedups, width=bar_width, color='#3498db', edgecolor='black')

    ax.set_title("Kernel Speedup (Multi-Core vs Single-Core)", fontsize=16)
    ax.set_ylabel("Speedup", fontsize=14)
    ax.set_xticks(x_pos)
    ax.set_xticklabels(kernel_labels, rotation=45, ha="right", fontsize=10)

    for bar in bars:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width() / 2., height + 0.05,
                f"{height:.2f}x",
                ha="center", va="bottom", fontsize=9, fontweight="bold")

    ax.axhline(8.0, color='red', linestyle='--', linewidth=1)
    ax.set_ylim(0, 10)

    plt.grid(axis="y", linestyle="--")
    plt.tight_layout()

    output_path = os.path.join(paths.graphs_dir, "kernel_speedup_chart.png")
    plt.savefig(output_path)
    plt.close(fig)

    print(f"Speedup chart saved to {output_path}")


def generate_gflops_bar_chart(paths, stats):
    kernel_names_all = list(stats.keys())
    kernel_names_all.sort()

    all_gflops_data = {name: compute_gflops(stats[name]) for name in kernel_names_all}
    filtered_kernels = [
        name for name, (sc_g, mc_g) in all_gflops_data.items() if mc_g > 0.0
    ]
    filtered_kernels.sort()

    sc_gflops = [all_gflops_data[name][0] for name in filtered_kernels]
    mc_gflops = [all_gflops_data[name][1] for name in filtered_kernels]
    kernel_labels = [name.replace("_", " ") for name in filtered_kernels]

    fig, ax = plt.subplots(figsize=(16, 7))

    bar_width = 0.35
    x_group_pos = np.arange(len(filtered_kernels)) * 1.5

    x_single = x_group_pos - bar_width/2
    x_multi = x_group_pos + bar_width/2

    color_single = '#f39c12'
    color_multi = '#2ecc71'

    bars_single = ax.bar(x_single, sc_gflops, width=bar_width, label='Single-Core GFLOPS', color=color_single, edgecolor='black')
    bars_multi = ax.bar(x_multi, mc_gflops, width=bar_width, label='Multi-Core GFLOPS', color=color_multi, edgecolor='black')

    ax.set_title(f"Kernel GFLOPS at {FREQUENCY_MHZ} MHz", fontsize=16)
    ax.set_ylabel("GFLOPS", fontsize=14)
    ax.set_xticks(x_group_pos)
    ax.set_xticklabels(kernel_labels, rotation=45, ha='right', fontsize=10)

    max_gflops = max(max(sc_gflops) if sc_gflops else 0, max(mc_gflops) if mc_gflops else 0)
    for bars in [bars_single, bars_multi]:
        for bar in bars:
            height = bar.get_height()
            ax.text(bar.get_x() + bar.get_width() / 2, height + 0.05, f'{height:.2f}', ha='center', va='bottom', fontsize=8)

    ax.set_ylim(0, max_gflops * 1.15 if max_gflops else 0)
    ax.legend(loc='upper left')

    plt.grid(axis='y', linestyle='--')
    plt.tight_layout()

    output_path = os.path.join(paths.graphs_dir, "kernel_gflops_chart.png")
    plt.savefig(output_path)
    plt.close(fig)
    print(f"GFLOPS chart saved to {output_path}")


def main():
    args = parse_args()
    paths = set_paths(args)
    stats = load_stats(paths)

    if not stats:
        print("Error retrieving stats")
        return

    generate_speedup_bar_chart(paths, stats)
    generate_gflops_bar_chart(paths, stats)

    print(f"\n --- All Graphs has been generated ---\n")

if __name__ == "__main__":
    main()
