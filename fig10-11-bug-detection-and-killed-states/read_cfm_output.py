#!/usr/bin/env python3
import os
import sys
import pandas as pd
import matplotlib.pyplot as plt
import re


def read_output(input_directory):

    # List to store each file's data
    records = []

    # Iterate over all .txt files in the directory
    for root, dirs, files in os.walk(input_directory):
        for file_name in files:
            if file_name.endswith(".txt"):
                file_path = os.path.join(root, file_name)
                with open(file_path, "r") as f:
                    lines = f.readlines()

                # Extract the time for CFM true error
                cfm_true_error = None
                no_cfm_error = None
                max_time = None
                for line in lines:
                    if "--max-time=" in line:
                        match = re.search(r"--max-time=(\d+)s", line)
                        if match:
                            max_time = float(match.group(1))
                    if "CFM found true error" in line:
                        cfm_true_error = float(line.split()[9])
                    if "ERROR found in non-transformed KLEE run" in line:
                        no_cfm_error = float(line.split()[9])

                        

                # If either time is missing, use max_time
                if cfm_true_error is None:
                    cfm_true_error = max_time
                if no_cfm_error is None:
                    no_cfm_error = max_time

                # Append a record for this file
                input_size = os.path.basename(file_path
                                             ).split(".")[0].split("_")[-1]

                records.append({
                    "input_size": int(input_size),
                    "cfm_true_error": cfm_true_error,
                    "no_cfm_error": no_cfm_error
                })

    # Create DataFrame and write to CSV
    df = pd.DataFrame(records)
    return df


def plot_graph(df, benchmark_name, unit):

    input_size = df["input_size"]
    cfm_true_error = df["cfm_true_error"]
    no_cfm_error = df["no_cfm_error"]

    if unit == "hours":
        cfm_true_error = cfm_true_error / 3600
        no_cfm_error = no_cfm_error / 3600

    # make a scatter plot
    plt.scatter(input_size, cfm_true_error, label='CFM-SE')
    plt.scatter(input_size, no_cfm_error, label='Original')
    # add grid
    plt.grid()

    # output the y values
    print("CFM-SE y values: ", cfm_true_error)
    print("KLEE y values: ", no_cfm_error)

    plt.xlabel('Input Size')
    plt.ylabel('Time (' + unit + ')')
    # plt.title('Time Until Bug')
    plt.legend()
    plt.xticks(input_size)
    # save the plot
    plt.savefig(f'{benchmark_name}.png')
    plt.savefig(f'{benchmark_name}.pdf')



if __name__ == "__main__":
    # get an integer argument from command line

    if len(sys.argv) != 4:
        print("Usage: python read_cfm_output.py <directory> <benchmark_name> <unit (seconds|hours)>")
        sys.exit(1)
    
    dfs = []

    print("Reading output from directories...")
    print(sys.argv)

    input_directory = sys.argv[1]
    # get all folders in the input_directory

    for folder in os.listdir(input_directory):
        if not os.path.isdir(os.path.join(input_directory, folder)):
            print(f"{folder} is not a directory.")
            sys.exit(1)
        df = read_output(os.path.join(input_directory, folder))
        dfs.append(df)

    
    df_final = pd.concat(dfs, axis=0)
    # df_final = df_final.dropna()
    df_avg = df_final.groupby('input_size', as_index=False)[['cfm_true_error', 'no_cfm_error']].mean()
    df_avg = df_avg.sort_values(by=["input_size"])
    df_avg.to_csv("output.csv", index=False)
    plot_graph(df_avg, sys.argv[2], sys.argv[3]) # benchmark name, unit




