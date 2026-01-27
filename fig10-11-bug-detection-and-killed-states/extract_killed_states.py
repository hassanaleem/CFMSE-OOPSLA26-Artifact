import sys
import subprocess
import os
import re
import glob

def extract_killed_states(directory):
    # get all directories inside the given directory that starts with klee-cfm
    cfmse_directories = [d for d in os.listdir(directory) if d.startswith("klee-cfm") and os.path.isdir(os.path.join(directory, d))]
    nocfmse_directories = [d for d in os.listdir(directory) if d.startswith("klee-nocfm") and os.path.isdir(os.path.join(directory, d))]
    cfmse_killed_states = 0
    nocfmse_killed_states = 0
    

    for directory in cfmse_directories:
        cmd = ["bash", "-c", f"$KLEE_STATS {directory} --print-columns 'KilledStates'"]
        result = subprocess.run(cmd, capture_output=True, text=True)

        match = re.search(r"\|\s*(\d+)\s*\|", result.stdout)
        if match:
            cfmse_killed_states += int(match.group(1))
        else:
            cfmse_killed_states += 0

    for directory in nocfmse_directories:
        cmd = ["bash", "-c", f"$KLEE_STATS {directory} --print-columns 'KilledStates'"]
        result = subprocess.run(cmd, capture_output=True, text=True)

        match = re.search(r"\|\s*(\d+)\s*\|", result.stdout)
        if match:
            nocfmse_killed_states += int(match.group(1))
        else:
            nocfmse_killed_states += 0

    return cfmse_killed_states, nocfmse_killed_states


def main():
    directory = sys.argv[1]
    size = sys.argv[2]


    cfmse_killed_states, nocfmse_killed_states = extract_killed_states(directory)
    # append this result to a csv file
    with open("killed_states.csv", "a") as f:
        f.write(f"{size},{cfmse_killed_states},{nocfmse_killed_states}\n")

if __name__ == "__main__":
    main()

