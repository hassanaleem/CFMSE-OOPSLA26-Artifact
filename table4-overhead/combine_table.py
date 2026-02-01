import pandas as pd
import glob
import os

dfs = []

for csv_file in glob.glob("*.csv"):
    df = pd.read_csv(csv_file)

    benchmark = os.path.splitext(csv_file)[0]
    df.insert(0, "benchmark", benchmark)

    dfs.append(df)

combined = pd.concat(dfs, ignore_index=True)
combined.to_csv("overhead.csv", index=False)
