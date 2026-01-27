

# # compile the files and extract the data
# import os


# libosip = "artifact/fig7-coverage/chopper-experiments/libosip"



# compile time overhead = time taken to compile
# LOC is number of lines of code from cloc source code (before cfmse)
# number of instructions before cfmse
# merges = number of successful applications of cfmse
# select overhead = selct instructions added by cfmse / total instructions after cfmse



import re
import argparse
import sys

def parse_log(logfile_path, loc_value):
    """
    Parses the LLVM opt pass log and returns a dictionary of metrics.
    """
    
    # --- Regex patterns to find our data ---
    # We capture the number (integer or float) at the end of the line
    patterns = {
        'instr_before': re.compile(r'Total Instructions before CFMSE : (\d+)'),
        'merges': re.compile(r'Number of successful applications of CFMSE : (\d+)'),
        'select_added': re.compile(r'Number of select instructions added : (\d+)'),
        'instr_after': re.compile(r'Total Instructions after CFMSE : (\d+)'),
        # For time, we find the line with CFMSEPass and grab the wall time
        # which is the second-to-last field, a float.
        'time_pass': re.compile(r'^\s*([\d\.]+)\s*\(.*CFMSEPass'),
    }
    
    # Dictionary to store the extracted data
    data = {
        'time_pass': 0.0,
        'instr_before': 0,
        'merges': 0,
        'select_added': 0,
        'instr_after': 0,
    }
    
    # --- Read and parse the log file ---
    try:
        with open(logfile_path, 'r') as f:
            for line in f:
                # Check each pattern against the line
                for key, pattern in patterns.items():
                    match = pattern.search(line)
                    if match:
                        # If a match is found, store the captured value
                        # We grab group(1), which is the part in parentheses ( )
                        if key == 'time_pass':
                            data[key] = float(match.group(1))  # Keep ms as is
                        else:
                            data[key] = int(match.group(1))
                        
                        # No need to check other patterns on this line
                        break
                        
    except FileNotFoundError:
        print(f"Error: Log file not found at {logfile_path}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}", file=sys.stderr)
        sys.exit(1)

    # --- Calculate the derived metrics ---
    data['loc'] = loc_value
    
    if data['instr_after'] > 0:
        data['select_overhead_pct'] = (data['select_added'] / data['instr_after']) * 100
    else:
        data['select_overhead_pct'] = 0
        
    return data

def main():

    
    # --- Get the data and print the CSV ---
    data = parse_log("libosip.txt", 0)
    
    # Define the CSV header
    header = [
        "CompileTime_ms", 
        "LOC", 
        "Instructions_Before", 
        "Merges", 
        "SelectOverhead_pct"
    ]
    
    # Define the corresponding data row
    row = [
        f"{data['time_pass']:.4f}",
        f"{data['loc']}",
        f"{data['instr_before']}",
        f"{data['merges']}",
        f"{data['select_overhead_pct']:.2f}"
    ]
    # Print the CSV header
    print(",".join(header))
        
    # Print the data row
    print(",".join(row))

if __name__ == "__main__":
    main()