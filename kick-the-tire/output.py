import pandas as pd
from tabulate import tabulate
import os
import glob # Used for finding all your CSV files

def process_benchmark_file(file_path):
    """
    Reads a single benchmark CSV, processes it, and returns a 
    DataFrame pivoted into the target table format.
    """
    try:
        df = pd.read_csv(file_path, skipinitialspace=True)
    except FileNotFoundError:
        print(f"Warning: File not found at {file_path}. Skipping.")
        return None

    # 1. Get the benchmark name from the filename
    benchmark_name = os.path.splitext(os.path.basename(file_path))[0]
    df['Benchmark'] = benchmark_name

    # 2. Melt the DataFrame
    # This turns it from "wide" (many columns) to "long" (many rows)
    id_vars = ['Benchmark', 'Input_Size']
    df_long = df.melt(id_vars=id_vars, var_name='Metric_Method', value_name='Value')

    # 3. Extract Metric and Method from "Metric_Method"
    # e.g., "Instrs-cfm-sm" -> Metric="Instrs", Method="cfm-sm"
    # This regex is robust for all your column names
    regex_pattern = r'^(.*)-(klee|cfm|sm|cfm-sm)$'
    df_long[['Metric', 'Method']] = df_long['Metric_Method'].str.extract(regex_pattern)

    # Handle any rows that didn't match (e.g., if there are parsing errors)
    df_long = df_long.dropna(subset=['Metric', 'Method'])

    # 4. Map names to the target table's format
    method_map = {
        'klee': 'K',
        'sm': 'SM',
        'cfm': 'C',
        'cfm-sm': 'C-SM'
    }
    metric_map = {
        'Time(s)': 'Time(s)',
        'Queries': 'Number of Queries',
        'AvgSolverQuerySize': 'Average Query Size',
        'Explored_Paths': 'Explored Paths'
        # Add any other metrics you want to rename
    }

    df_long['Method'] = df_long['Method'].map(method_map)
    # Use .get() to map, with the original value as a default if not in map
    df_long['Metric'] = df_long['Metric'].apply(lambda x: metric_map.get(x, x))
    
    # 5. Handle "Out of Time" (OOT) for Time(s) metric
    # Convert 'Value' to numeric, setting non-numeric to NaN (Not a Number)
    numeric_values = pd.to_numeric(df_long['Value'], errors='coerce')
    
    # Create conditions
    # Condition 1: The metric is 'Time(s)'
    is_time_metric = df_long['Metric'] == 'Time(s)'
    # Condition 2: The numeric value is greater than 60
    is_over_time = numeric_values > 60
    
    # Apply the "OOT" string where both conditions are True
    # We use .loc to modify the DataFrame in place
    df_long.loc[is_time_metric & is_over_time, 'Value'] = 'OOT'

    # 6. Pivot the data into the final table structure
    # This is the key step that creates the multi-level columns
    # The 'Value' column now contains mixed types (numbers and 'OOT' strings)
    # pivot_table handles this correctly.
    df_pivot = df_long.pivot_table(
        index=['Benchmark', 'Input_Size'],
        columns=['Metric', 'Method'],
        values='Value',
        aggfunc='first' # Use 'first' as aggfunc for mixed types
    )
    
    return df_pivot


if __name__ == "__main__":
    
    # --- Part 2: Process ALL benchmarks and combine them ---
    print("\n\n--- Processing all .csv files in the directory ---")
    
    # Use glob to find all .csv files in the current directory
    # You can change this pattern, e.g., to "./benchmarks/*.csv"
    all_benchmark_files = glob.glob('./*.csv')
    
    # To avoid re-processing this script, remove it from the list if it's a .csv
    try:
        script_name = f"./{os.path.basename(__file__)}"
        if script_name in all_benchmark_files:
            all_benchmark_files.remove(script_name)
    except ValueError:
        pass # It wasn't in the list, no problem

    print(f"Found files: {all_benchmark_files}")

    all_tables = []
    for f in all_benchmark_files:
        # Skip the combined results file if it already exists
        if f == './combined_benchmark_results.csv':
            continue
            
        print(f"Processing {f}...")
        processed_table = process_benchmark_file(f)
        if processed_table is not None:
            all_tables.append(processed_table)

    if not all_tables:
        print("No valid benchmark CSVs found to process.")
    else:
        # 6. Combine all individual tables into one big table
        final_table = pd.concat(all_tables)

        # 7. (Optional) Reorder columns to match your image
        metric_order = ['Time(s)', 'Number of Queries', 'Average Query Size', 'Explored Paths']
        method_order = ['K', 'SM', 'C', 'C-SM']

        # Get all metrics present, but start with your preferred ones
        all_present_metrics = final_table.columns.get_level_values(0).unique()
        final_metric_order = metric_order + [m for m in all_present_metrics if m not in metric_order]

        # Apply the reordering
        final_table = final_table.reindex(columns=final_metric_order, level=0)
        final_table = final_table.reindex(columns=method_order, level=1)

        # 8. Print and Save the final result
        print("\n\n--- Combined Table for All Benchmarks ---")
        print(tabulate(final_table, headers='keys', tablefmt='psql'))
        
        output_filename = 'table3.csv'
        final_table.to_csv(output_filename)
        print(f"\nSuccessfully saved combined table to '{output_filename}'")
