#!/usr/bin/env python3
import os
import sys
import pandas as pd

def main(input_directory):

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
                for line in lines:
                    if "CFM found true error" in line:
                        try:
                            # Assuming the time is at index 7 and converting to float
                            cfm_true_error = float(line.split()[9])
                        except (IndexError, ValueError):
                            cfm_true_error = None
                        break

                # Extract the time for no-cfm error
                no_cfm_error = None
                for line in lines:
                    if "ERROR found in non-transformed KLEE run" in line:
                        try:
                            # Assuming the time is at index 7 and converting to float
                            no_cfm_error = float(line.split()[9])
                        except (IndexError, ValueError):
                            no_cfm_error = None
                        break

                # Append a record for this file
                input_size = os.path.basename(file_path
                                             ).split(".")[0].split("_")[-1]

                records.append({
                    "input_size": input_size,
                    "cfm_true_error": cfm_true_error,
                    "no_cfm_error": no_cfm_error
                })

    # Create DataFrame and write to CSV
    df = pd.DataFrame(records)
    return df


df1 = main("./logs_high_value/logs_1")
df2 = main("./logs_high_value/logs_2")
df3 = main("./logs_high_value/logs_3")

df_final = pd.concat([df1, df2, df3], axis=0)
df_avg = df_final.groupby('input_size', as_index=False)[['cfm_true_error', 'no_cfm_error']].mean()
df_avg.to_csv("output.csv", index=False)

