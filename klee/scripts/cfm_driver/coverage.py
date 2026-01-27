#!/usr/bin/python3
import sys
import os
import re
import glob
import pandas as pd
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

def plot_cov(bench_name, klee_nocfm_outputdir, klee_cfm_outputdir):

    nocfm_coverage_file = klee_nocfm_outputdir + "/coverage.csv"

    # check if the coverage file exists
    if not os.path.isfile(nocfm_coverage_file):
        print(f"Error: {nocfm_coverage_file} does not exist!")
        sys.exit(1)

    # print the name of the coverage file
    print(f"Found nocfm coverage file: {nocfm_coverage_file}")

    nocfm_df = pd.read_csv(nocfm_coverage_file, header=None)
    nocfm_df.columns = ["epoch", "coverage"]
    # print(nocfm_df.head())
    cfm_df = pd.DataFrame()
    
    # get all files of the form klee_cfm_outputdir_*/coverage.csv
    cfm_dirs = glob.glob(klee_cfm_outputdir)

    for cfm_dir in cfm_dirs:
        cfm_coverage_file = cfm_dir + "/coverage.csv"

        # check if the coverage file exists
        if not os.path.isfile(cfm_coverage_file):
            print(f"Error: {cfm_coverage_file} does not exist!")
            sys.exit(1)

        # print the name of the coverage file
        print(f"Found cfm coverage file: {cfm_coverage_file}")

        # read the dataframe
        coverage_df = pd.read_csv(cfm_coverage_file, header=None)
        # print(coverage_df.head())
        coverage_df.columns = ["epoch", "coverage"]
        
        if cfm_df.empty:
            cfm_df = coverage_df
        else:
            # cfm_df = cfm_df.append(coverage_df, ignore_index=True)
            cfm_df = pd.concat([cfm_df, coverage_df], ignore_index=True)

        
    
    # print(cfm_df)
    nocfm_x_values = nocfm_df["epoch"].tolist()
    nocfm_x_values = [x - nocfm_x_values[0] for x in nocfm_x_values]
    nocfm_y_values = nocfm_df["coverage"].tolist()

    cfm_x_values = cfm_df["epoch"].tolist()
    cfm_x_values = [x - cfm_x_values[0] for x in cfm_x_values]
    cfm_y_values = cfm_df["coverage"].tolist()

    plt.figure()
    # plot nocfm_y_values vs nocfm_x_values
    plt.plot(nocfm_x_values, nocfm_y_values, label="KLEE")
    plt.plot(cfm_x_values, cfm_y_values, label="CFM-SE")
    plt.legend()
    plt.xlabel("Time (s)")
    plt.ylabel("Coverage (%)")
    plt.savefig(f"{bench_name}.pdf")

def extract_bench_name(driver_output_file):
    # extract the benchmark name from the driver output file using regex
    # e.g. driver_output_base64.txt -> base64
    bench_name = re.search(r"driver_output_(.*).txt", driver_output_file).group(1)
    return bench_name
    
def main():

    input_dir = sys.argv[1]
    # recursively find all files with the name driver_output_*.txt
    driver_output_files = glob.glob(input_dir + "/**/driver_output_*.txt", recursive=True)
    
    for dout_file in driver_output_files:
        # get benchmark name
        bench_name = extract_bench_name(dout_file)
        print(f"Processing benchmark : {bench_name}")

        # read all lines from the driver output file and find the line containing string "CFM output files in path  :"
        klee_cfm_outputdir = ""
        klee_nocfm_outputdir = ""
        with open(dout_file, "r") as f:
            for line in f:
                if "(main) : CFM output files in path  :" in line:
                    # extract the path to the klee-cfm output directory
                    klee_cfm_outputdir = line.split(":")[-1].strip()
                    # print(klee_cfm_outputdir)
                if "(main) : KLEE output files in path :" in line:
                    # extract the path to the klee-cfm output directory
                    klee_nocfm_outputdir = line.split(":")[-1].strip()
                    # print(klee_nocfm_outputdir)

        # if klee_cfm_outputdir or klee_nocfm_outputdir does not include coverage.csv,
        # then print an error message and exit
        cov_files_cfm = glob.glob(klee_cfm_outputdir + "/**/coverage.csv", recursive=True)
        cov_files_nocfm = glob.glob(klee_nocfm_outputdir + "/**/coverage.csv", recursive=True)

        if not cov_files_cfm or not cov_files_nocfm:
            print(f"Error: Could not find coverage files in {klee_cfm_outputdir} or {klee_nocfm_outputdir}")
        else:
            plot_cov(bench_name, klee_nocfm_outputdir, klee_cfm_outputdir)

def main_():
    plot_cov("unknown", sys.argv[1], sys.argv[2])

if __name__ == "__main__":
    # print(len(sys.argv))
    if len(sys.argv) > 2:
        main_()
    else:
        main()