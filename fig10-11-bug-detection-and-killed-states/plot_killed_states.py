import pandas as pd
import matplotlib.pyplot as plt
from sys import argv


def plot_killed_states(csv_file, dirname):
    data = pd.read_csv(csv_file, header=None, names=["Size", "CFMSE_Killed_States", "NoCFMSE_Killed_States"])
    # take mean if there are multiple entries for the same size
    data = data.groupby("Size").mean().reset_index()

    plt.figure(figsize=(10, 6))
    plt.plot(data["Size"], data["CFMSE_Killed_States"], label='CFM-SE')
    plt.plot(data["Size"], data["NoCFMSE_Killed_States"], label='Original')
    
    plt.xlabel('Input Size')
    plt.ylabel('Number of Killed States')
    plt.legend()
    plt.savefig(f"{dirname}/killed_states.png")
    plt.savefig(f"{dirname}/killed_states.pdf")
    plt.close()


def main():
    name = argv[1]
    plot_killed_states(f"{name}/killed_states.csv", name)

if __name__ == "__main__":
    main()  
