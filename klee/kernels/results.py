import os
import pandas as pd
import numpy as np
import glob
import sys
import pandas as pd
import optparse as op

input_sizes = {'toupper': [10, 50, 100], 'connected_comp': [3, 4, 5], 'kruskal': [3, 4, 5], 'prim': [
    4, 5, 6], 'transitive_closure': [3, 4, 5], 'detect_edges': [3, 4, 5], 'dilation': [4, 5, 6], 'erosion': [4, 5, 6], 'bitonic_sort': [4, 8, 16], 'floyd_warshall': [3, 4, 5], 'merge_sort' : [5, 10, 15], 'regex-bug': [5, 10]}
stats_from_klee_stat = ['Instrs', 'Time(s)', 'Queries', 'QCexCHits', 'TSolver(%)', 'AvgSolverQuerySize',
         'MaxMem(MiB)']
other_stats = ['Explored_Paths', 'Generated_Tests', 'Completed_Paths']

result_dict = {'bench_dirmark': [], 'Input_Size': [], 
               'Instrs-klee': [],'Instrs-cfm': [],'Instrs-sm': [],'Instrs-cfm-sm': [], 
               'Time(s)-klee': [],'Time(s)-cfm': [], 'Time(s)-sm': [], 'Time(s)-cfm-sm': [], 
               'Queries-klee': [],'Queries-cfm': [],'Queries-sm': [],'Queries-cfm-sm': [], 
                'QCexCHits-klee': [],'QCexCHits-cfm': [],'QCexCHits-sm': [],'QCexCHits-cfm-sm': [],
               'TSolver(%)-klee': [],'TSolver(%)-cfm': [],'TSolver(%)-sm': [],'TSolver(%)-cfm-sm': [],
               'AvgSolverQuerySize-klee': [],'AvgSolverQuerySize-cfm': [],'AvgSolverQuerySize-sm': [],'AvgSolverQuerySize-cfm-sm': [],
               'MaxMem(MiB)-klee': [],'MaxMem(MiB)-cfm': [],'MaxMem(MiB)-sm': [],'MaxMem(MiB)-cfm-sm': [],
               'Explored_Paths-klee': [], 'Explored_Paths-cfm': [], 'Explored_Paths-sm': [], 'Explored_Paths-cfm-sm': [], 
               'Generated_Tests-klee': [], 'Generated_Tests-cfm': [],'Generated_Tests-sm': [],'Generated_Tests-cfm-sm': [],
               'Completed_Paths-klee': [], 'Completed_Paths-cfm': [], 'Completed_Paths-sm': [],'Completed_Paths-cfm-sm': []}
results = pd.DataFrame(result_dict)


def extract_value_from_file(f):

    out = {'Explored_Paths': 'NA', 'Generated_Tests': 'NA', 'Completed_Paths': 'NA'}

    if not os.path.exists(f):
        return out
    
    explored_paths = 'NA'
    generated_tests = 'NA'
    completed_paths = 'NA'

    with open(f) as f:
        for line in f:
            if 'KLEE: done: explored paths' in line:
                explored_paths = int(line.split(' = ')[1])
            if 'KLEE: done: generated tests' in line:
                generated_tests = int(line.split(' = ')[1])
            if 'KLEE: done: completed paths' in line:
                completed_paths = int(line.split(' = ')[1])

    
    out['Explored_Paths'] = explored_paths
    out['Generated_Tests'] = generated_tests
    out['Completed_Paths'] = completed_paths
    return out

def print_klee_stats(bench_dir, input_size, methods = ["klee", "klee_cfm", "klee_sm", "klee_cfmsm"]):

    # create empty dataframes for klee, klee_cfm, klee_sm and klee_cfmsm
    df_klee = pd.DataFrame()
    df_klee_cfm = pd.DataFrame()
    df_klee_sm = pd.DataFrame()
    df_klee_cfmsm = pd.DataFrame()

    # list files for 4 techniques
    files_klee = glob.glob(bench_dir + f'/{methods[0]}_stats_{input_size}_*.csv')
    files_cfm = glob.glob(bench_dir + f'/{methods[1]}_stats_{input_size}_*.csv')
    files_sm = glob.glob(bench_dir + f'/{methods[2]}_stats_{input_size}_*.csv')
    files_cfmsm = glob.glob(
        bench_dir + f'/{methods[3]}_stats_{input_size}_*.csv')

    # if any of above list is empty, print error message and exit
    if len(files_klee) == 0 and len(files_cfm) == 0 and len(files_sm) == 0 and len(files_cfmsm) == 0:
        print(
            f'Error: No files found for {bench_dir} with input size {input_size}')
        exit(-1)

    print("Reading following files:")
    print("Files for klee: ", files_klee)
    print("Files for klee_cfm: ", files_cfm)
    print("Files for klee_sm: ", files_sm)
    print("Files for klee_cfmsm: ", files_cfmsm)

    for f in files_klee:
        # read csv file and append the last row to the dataframe
        df_klee = pd.concat([df_klee, pd.read_csv(f).tail(1)])

    for f in files_cfm:
        # read csv file and append the last row to the dataframe
        df_klee_cfm = pd.concat([df_klee_cfm, pd.read_csv(f).tail(1)])

    for f in files_sm:
        # read csv file and append the last row to the dataframe
        df_klee_sm = pd.concat([df_klee_sm, pd.read_csv(f).tail(1)])

    for f in files_cfmsm:
        # read csv file and append the last row to the dataframe
        df_klee_cfmsm = pd.concat([df_klee_cfmsm, pd.read_csv(f).tail(1)])

    # print(df_klee['Queries'])
    # print(df_klee_cfmsm['Queries'])

    # print the median of the stats for each dataframe
    klee_stats = []
    for stat in stats_from_klee_stat:
        klee_val = df_klee[stat].median() if stat in df_klee.columns else "NA"
        klee_cfm_val = df_klee_cfm[stat].median() if stat in df_klee_cfm.columns else "NA"
        klee_sm_val = df_klee_sm[stat].median() if stat in df_klee_sm.columns else "NA"
        klee_cfmsm_val = df_klee_cfmsm[stat].median() if stat in df_klee_cfmsm.columns else "NA"

        klee_stats = klee_stats + [klee_val, klee_cfm_val, klee_sm_val, klee_cfmsm_val]

    log_file_klee_name =  f'{methods[0]}_{input_size}_1.log'
    log_file_cfm_name =  f'{methods[1]}_{input_size}_1.log'
    log_file_sm_name =  f'{methods[2]}_{input_size}_1.log'
    log_file_cfmsm_name =  f'{methods[3]}_{input_size}_1.log'

    # print(bench_dir + log_file_klee_name)
    log_file_klee = glob.glob(bench_dir + '/' + log_file_klee_name)[0] if glob.glob(bench_dir +'/' + log_file_klee_name) else "NA"
    log_file_cfm = glob.glob(bench_dir +'/' + log_file_cfm_name)[0] if glob.glob(bench_dir +'/' + log_file_cfm_name) else "NA"
    log_file_sm = glob.glob(bench_dir +'/' + log_file_sm_name)[0] if glob.glob(bench_dir +'/' + log_file_sm_name) else "NA"
    log_file_cfmsm = glob.glob(
        bench_dir +'/' + log_file_cfmsm_name)[0] if glob.glob(bench_dir + '/'+ log_file_cfmsm_name) else "NA"

    print("Reading following log files:")
    print("Log file for klee: ", log_file_klee)
    print("Log file for klee_cfm: ", log_file_cfm)
    print("Log file for klee_sm: ", log_file_sm)
    print("Log file for klee_cfmsm: ", log_file_cfmsm)

    # open log_file_klee and itearte over the lines
    other_stats_klee = extract_value_from_file(log_file_klee)
    other_stats_cfm = extract_value_from_file(log_file_cfm)
    other_stats_sm = extract_value_from_file(log_file_sm)
    other_stats_cfmsm = extract_value_from_file(log_file_cfmsm)

    for stat in other_stats:
        klee_stats = klee_stats + [other_stats_klee[stat], other_stats_cfm[stat], other_stats_sm[stat], other_stats_cfmsm[stat]]

    
    results.loc[len(results)] = [bench_dir, input_size] + klee_stats




if __name__ == '__main__':

    # define an argument parser
    parser = op.OptionParser()
    # add optioin to specify the directory of the benchmark and store it in bench_dir
    parser.add_option('-b', '--bench_dir', dest='bench_dir', help='directory of the benchmark')
    # add option to specify the verify flag
    parser.add_option('-v', '--verify', dest='verify', action='store_true', help='print verify data')

    # parse the arguments
    (options, args) = parser.parse_args()

    # extract bench mark name from the bench_dir
    bench_name = options.bench_dir.split('/')[0]


    for input_size in input_sizes[bench_name]:
        if not options.verify:
            print_klee_stats(options.bench_dir, input_size)
        else:
            print_klee_stats(options.bench_dir, input_size, methods = ["klee_verify", "klee_cfm_verify", "klee_sm_verify", "klee_cfmsm_verify"])
        


    csv_str = results.to_csv(index=False)
    print(csv_str)
    fname = bench_name + ".csv"
    with open(fname, "w", newline="") as f:
        f.write(csv_str)