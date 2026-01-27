import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_coverage_graph(klee_file, cfm_file, benchmark_name):
    files = {
        "CFM-SE": cfm_file,
        "Original": klee_file,
    }

    plt.plot()

    for label, path in files.items():
        df = pd.read_csv(path, header=None, names=["timestamp","coverage"])
        # normalize time to start at 0
        t0 = df["timestamp"].iloc[0]
        x = df["timestamp"] - t0
        y = df["coverage"]
        # x less than 150 
        x = x[x < 150]
        y = y[:len(x)]
        # plot with label
        plt.plot(x, y, label=label)


    # draw a veritical line at last point in cfm_file
    # cfm_df = pd.read_csv(cfm_file, header=None, names=["timestamp","coverage"])
    # t0 = cfm_df["timestamp"].iloc[0]
    # last_time = cfm_df["timestamp"].iloc[-1] - t0
    # plt.axvline(x=last_time, color='grey', linestyle='--')

    plt.xlabel("Time since start (s)")
    plt.ylabel("Coverage (%)")
    # plt.title("Coverage vs Time")
    plt.legend()
    plt.tight_layout()
    plt.show()
    plt.savefig(f"{benchmark_name}_coverage_graph.pdf")

if __name__ == "__main__":
    # get filenames from args
    cfm_file = sys.argv[1]
    klee_file = sys.argv[2]
    # process benchmakr name from klee_file 
    # python3 ${KLEE_BUILD_DIR}/../scripts/coverage_graph.py $main_dir/$benchName/coverage-cfmse.csv $main_dir/$benchName/coverage-nocfmse.csv

    print("KLEE file:", klee_file)

    benchmark_name = klee_file.split("/")[-2]

    print("Benchmark name:", benchmark_name) 

    plot_coverage_graph(klee_file, cfm_file, benchmark_name)

