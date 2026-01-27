import glob
import re
import subprocess
import matplotlib.pyplot as plt
import numpy as np


# --- Dictionaries to store results ---
cfmse_partial_paths = {}
cfmse_completed_paths = {}

regular_partial_paths = {}
regular_completed_paths = {}

regular_time = {}
cfmse_time = {}

completed_pattern = re.compile(r"KLEE: done: completed paths = (\d+)")

partial_pattern = re.compile(r"KLEE: done: partially completed paths = (\d+)")


def read_time(type: str) -> float:
    
    # get all directories that start with {type}-size-x
    dir_pattern = f"{type}-size-*"
    dir_names = glob.glob(dir_pattern)

    for dir_name in dir_names:
        # if dirname ends with .txt, skip
        if dir_name.endswith(".txt"):
            continue
        size = int(dir_name.split("-")[-1])
        cmd = ["bash", "-c", f"$KLEE_STATS {type}-size-{size} --print-columns 'Time(s)'"]
        result = subprocess.run(cmd, capture_output=True, text=True)

        match = re.search(r"\|\s*([\d.]+)\s*\|", result.stdout)
        if match:
            time = float(match.group(1))
        else:
            time = -1.0
        if type == "cfmse":
            cfmse_time[size] = time
        elif type == "regular":
            regular_time[size] = time

def read_paths(type: str):    
    if type == "cfmse":
        completed_paths_dict = cfmse_completed_paths
        partial_paths_dict = cfmse_partial_paths
    elif type == "regular":
        completed_paths_dict = regular_completed_paths
        partial_paths_dict = regular_partial_paths

    file_names = glob.glob(f"{type}-size-*/info")

    for file_name in file_names:
        size = int(file_name.split("-")[-1].split("/")[0])

        completed_paths_dict[size] = 0
        partial_paths_dict[size] = 0

        with open(file_name, "r") as f:
            for line in f:

                completed_match = completed_pattern.search(line)
                if completed_match:

                    count = int(completed_match.group(1))
                    completed_paths_dict[size] = count

                partial_match = partial_pattern.search(line)
                if partial_match:
                    count = int(partial_match.group(1))
                    partial_paths_dict[size] = count

def plot_graphs():
    input_sizes = sorted(regular_time.keys())

    plt.figure(figsize=(12, 6))

    # Plotting completed paths
    plt.plot(input_sizes, [np.log10(cfmse_completed_paths[size]) for size in input_sizes], label="CFM-SE")
    plt.plot(input_sizes, [np.log10(regular_completed_paths[size]) for size in input_sizes], label="Original")
    plt.xlabel("Input Size")
    plt.ylabel("Number of Completed Paths (log10 scale)")
    plt.legend()
    plt.savefig("fig6b.png")
    plt.clf()

    # Plotting time taken
    plt.plot(input_sizes, [np.log10(cfmse_time[size]) for size in input_sizes], label="CFM-SE")
    plt.plot(input_sizes, [np.log10(regular_time[size]) for size in input_sizes], label="Original")
    plt.xlabel("Input Size")
    plt.ylabel("Time (s) (log10 scale)")
    plt.legend()
    plt.savefig("fig6a.png")
    plt.clf()

    # plotting total paths (completed + partial)
    plt.plot(input_sizes, [np.log10(cfmse_completed_paths[size] + cfmse_partial_paths[size]) for size in input_sizes], label="CFM-SE")
    plt.plot(input_sizes, [np.log10(regular_completed_paths[size] + regular_partial_paths[size]) for size in input_sizes], label="Original")
    plt.xlabel("Input Size")
    plt.ylabel("Total Paths (log10 scale)")
    plt.legend()
    plt.savefig("fig6c.png")
    plt.clf()



# --- Main execution block ---
if __name__ == "__main__":
    read_paths("cfmse")
    read_paths("regular")
    read_time("cfmse")
    read_time("regular")
    plot_graphs()



