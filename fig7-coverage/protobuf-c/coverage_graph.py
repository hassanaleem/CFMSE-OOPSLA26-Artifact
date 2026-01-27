import pandas as pd
import matplotlib.pyplot as plt
import sys

def plot_coverage_graph(klee_file, cfm_file):
    files = {
        "CFM": cfm_file,
        "Original": klee_file,
    }

    plt.plot()

    for label, path in files.items():
        df = pd.read_csv(path, header=None, names=["timestamp","coverage"])
        # normalize time to start at 0
        t0 = df["timestamp"].iloc[0]
        x = df["timestamp"] - t0
        y = df["coverage"]
        x = x[x <= 1500]
        y = y[:len(x)]

        plt.plot(x, y, label=label)

    plt.xlabel("Time since start (s)")
    plt.ylabel("Coverage (%)")
    plt.title("Coverage vs Time")
    plt.legend()
    plt.tight_layout()
    plt.show()
    plt.savefig("protobuf.pdf")

if __name__ == "__main__":
    # get filenames from args
    cfm_file = sys.argv[1]
    klee_file = sys.argv[2]
    print("CFM file:", cfm_file)
    print("KLEE file:", klee_file)
    plot_coverage_graph(klee_file, cfm_file)

