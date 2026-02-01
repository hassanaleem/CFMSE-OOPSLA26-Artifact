

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
    
    try:
        with open(logfile_path, 'r') as f:
            for line in f:
                # Check each pattern against the line
                for key, pattern in patterns.items():
                    match = pattern.search(line)
                    if match:
                        if key == 'time_pass':
                            data[key] = float(match.group(1))  
                        else:
                            data[key] = int(match.group(1))
                        
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

    file = sys.argv[1]
    # --- Get the data and print the CSV ---
    data = parse_log(file, 0)
    
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
    # save to a csv file
    with open(f"{file}.csv", "w") as f:
        f.write(",".join(header) + "\n")
        f.write(",".join(row) + "\n")

    # print(",".join(row))

if __name__ == "__main__":
    main()