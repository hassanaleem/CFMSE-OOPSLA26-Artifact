#!/usr/bin/python3
import subprocess
import os
import re
import time
import multiprocessing
import json
import signal
import sys
import glob
from utils import debug_print, getErrorLocationInformation
from utils import keyboard_exit_handler, set_default
from utils import parse_time_from_option_string
from utils import get_prog_name_from_bc_path
from utils import executeKleeWithoutTransformation
from utils import FalsePositiveDict
from utils import analyzeErroringTest 

# Register the signal handler for SIGINT signal
signal.signal(signal.SIGINT, keyboard_exit_handler)

def run_main_exit_on_error(input_bitcode, config, run_in_dir, dry_run=False):

    klee_options = str(config['KLEE_OPTIONS'])

    # if klee_options does not contain --max-time option, print error and exit
    if not "-max-time" in klee_options:
        debug_print(f"Error: --max-time option not found in KLEE options!" , tag="main")
        sys.exit(1)

    # if klee_options does not contain --exit-on-error option add it
    if "-exit-on-error" not in klee_options:
        klee_options += " --exit-on-error "

    # if .env file exists in run_in_dir, update the klee_options
    if os.path.isfile(run_in_dir+"/test.env"):
        klee_options += f" --env-file={run_in_dir}/test.env "

    # parse the --max-time option from the KLEE options
    [max_time_in_seconds, klee_options_without_time] = parse_time_from_option_string(klee_options)

    # klee options for without transformation
    klee_without_cfm_options = klee_options_without_time + f" --max-time={max_time_in_seconds}s --run-in-dir={run_in_dir}/klee-rundir/sandbox "

    # klee options for with transformation (but without --max-time option)
    klee_cfm_options_without_time = klee_options_without_time + f" {str(config['CFM_OPTIONS'])} "

    # if run_in_dir does not exist, print error and exit
    if not os.path.isdir(run_in_dir):
        debug_print(f"Error: {run_in_dir} does not exist!" , tag="main")
        sys.exit(1)

    # if run_in_dir is not an abosolute path, make it an absolute path
    if not os.path.isabs(run_in_dir):
        run_in_dir = os.path.abspath(run_in_dir)

    # check if run_in_dir+"/klee-rundir/sandbox" and run_in_dir+"/cfm-rundir/sandbox" exist
    # if not print error and exit
    if not os.path.isdir(run_in_dir+"/klee-rundir/sandbox"):
        debug_print(f"Error: {run_in_dir}/klee-rundir/sandbox does not exist!" , tag="main")
        sys.exit(1)
    
    if not os.path.isdir(run_in_dir+"/cfm-rundir/sandbox"):
        debug_print(f"Error: {run_in_dir}/cfm-rundir/sandbox does not exist!" , tag="main")
        sys.exit(1)

    # if input_bitcode file does not exist, print error and exit
    if not os.path.isfile(input_bitcode):
        debug_print(f"Error: {input_bitcode} does not exist!", tag="main")
        sys.exit(1)

    # if input_bitcode is not an abosolute path, make it an absolute path
    if not os.path.isabs(input_bitcode):
        input_bitcode = os.path.abspath(input_bitcode)

    # get current epoch time
    current_epoch = time.time()

    # get the program name from the input bitcode file
    prog_name = get_prog_name_from_bc_path(input_bitcode)

    # create klee-cfm-run-<epoch-time> and klee-nocfm-<epoch-time> directories
    klee_cfm_dir = os.path.join(run_in_dir, f"klee-cfm-run-{prog_name}-" + str(int(current_epoch)))
    klee_nocfm_dir = os.path.join(run_in_dir, f"klee-nocfm-{prog_name}-" + str(int(current_epoch)))

    # get process start time
    start_time = time.time()

    if dry_run:
        debug_print(f"KLEE without CFM options : {klee_without_cfm_options}", tag="main")
        debug_print(f"KLEE with CFM options : {klee_cfm_options_without_time}", tag="main")
        return

    # spawn a new process to execute KLEE without transformation
    debug_print(f"Running klee without the transformation on {input_bitcode}", tag="main")
    klee_without_transform_process=multiprocessing.Process(
        target=executeKleeWithoutTransformation, args=(config, input_bitcode, start_time, klee_without_cfm_options + f" --output-dir={klee_nocfm_dir} "))
    klee_without_transform_process.start()

    # false positives info
    false_positives_store = FalsePositiveDict()

    # number of times KLEE has been re-executed with transformation
    iteration = 0

    # keep re-executing KLEE with transformation until time limit is reached
    while time.time() - start_time < max_time_in_seconds:
        time_reminaing = max_time_in_seconds - int(time.time() - start_time)

        # Execute KLEE with transformation on program
        klee_with_cfm_options = f" {klee_cfm_options_without_time} --max-time={time_reminaing}s --run-in-dir={run_in_dir}/cfm-rundir/sandbox "

        klee_cfm_output_dirname = f"{klee_cfm_dir}_{iteration}"

        if false_positives_store.size() == 0:  # no false positives so far
            command = f"{str(config['KLEE_BIN']())} {klee_with_cfm_options} --output-dir={klee_cfm_output_dirname} {input_bitcode} {str(config['PROG_ARGS'])}"
        else: # there are false positives, ask CFM not to touch them plus seed from previous iteration
            command = f"{str(config['KLEE_BIN']())} {klee_with_cfm_options} -klee-cfmse-dont-touch-locs={run_in_dir}/{str(config['CFMSE_IGNORE_JSON'])} --output-dir={klee_cfm_output_dirname} --seed-dir={klee_cfm_dir}_{iteration-1} {input_bitcode} {str(config['PROG_ARGS'])}"

        debug_print("Executing : " + command, tag="main")

        process=subprocess.Popen(
            command, stderr=subprocess.PIPE, stdout=subprocess.DEVNULL, shell=True)

        while True:
            # Read a line from the subprocess's standard output
            output=process.stderr.readline()
            output_str=output.decode().strip()

            debug_print(output_str, tag="klee_cfm_stdout")

            if b'KLEE: ERROR: EXITING ON ERROR:' in output:
                error_time = time.time() - start_time
                debug_print(f"ERROR found in CFM-transformed KLEE run in {error_time} seconds!", tag="klee_cfm_stdout")

            # If there's no more output, break the loop
            if output == b'' and process.poll() is not None:
                break

        # Get the subprocess's return code
        return_code=process.poll()

        # Print the return code
        if (return_code == 0):
            debug_print("Symbolic execution with CFM finished successfully", tag="main")
        else:
            debug_print("Symbolic execution with transform failed!", tag="main")

        # check in the klee_cfm_dir for files with .err extension using glob
        klee_err_files = glob.glob(klee_cfm_output_dirname + "/*.err")

        if not klee_err_files:
            debug_print("No error files found! Exiting the driver loop..!", tag="main")
            break

        if len(klee_err_files) > 1:
            debug_print("WARN : More than one error file found.. Exiting the driver loop..!", tag="main")
            break

        ktest_err_file = klee_err_files[0]

        true_error = False
        # if .err file is a .model.err file then its a true error
        if ktest_err_file.endswith(".model.err"):
            debug_print("Memory limit error detected!", tag="main")
            true_error = True
        else:
            # get the erro location info
            (filename, funcname, lineno) = getErrorLocationInformation(ktest_err_file)

            # from ktest.err file, find the test number of the form test[0-9]+.ktest
            # using regex
            test_num = re.search(r"test[0-9]+", ktest_err_file).group(0)
            ktest_file = os.path.join(klee_cfm_output_dirname, test_num + ".ktest")

            # options for replay test
            klee_options_for_false_pos_check = f" {klee_options_without_time} --run-in-dir={run_in_dir}/cfm-rundir/sandbox --output-dir={run_in_dir}/FP_test_out_{iteration} "
            true_error = analyzeErroringTest(config, ktest_file, input_bitcode, (filename, funcname, lineno), klee_options_for_false_pos_check)

        if true_error:
            debug_print(f"KLEE with CFM found true error in {int(time.time() - start_time)} seconds", tag="main")
            debug_print("Exiting the driver loop..!", tag="main")
            break

        debug_print(f"KLEE with CFM found a false positive in {int(time.time() - start_time)} seconds", tag="main")
        debug_print("Updading false positives info..!", tag="main")

        # if this false positive is already in the dictionary, print an error and exit loop
        if false_positives_store.hasLocInfo(filename, funcname, lineno):
            debug_print("False positive already found! Exiting the driver loop..!", tag="main")
            break

        # add this false positive to the dictionary
        false_positives_store.addLocInfo(filename, funcname, lineno)

        # print the current false positives
        debug_print("False positives so far : ", tag="main")
        debug_print(false_positives_store.getDict(), tag="main")


        # dumps false positive location information to json so klee can use in next iteration
        cfmse_ignore_json = f"{run_in_dir}/" + str(config["CFMSE_IGNORE_JSON"])
        with open(cfmse_ignore_json, "w") as outfile:
            json.dump(false_positives_store.getDict(), outfile, default=set_default)

        debug_print("New false positive found! Re-executing KLEE with transformation..", tag="main")
        iteration += 1

    if klee_without_transform_process.is_alive():
        debug_print("Waiting for KLEE without Transformation to finish execution",  tag="main")

    klee_without_transform_process.join()
    debug_print("Driver finished execution!", tag="main")

    debug_print(f"CFM output files in path  : {klee_cfm_dir}_*", tag="main")
    debug_print(f"KLEE output files in path : {klee_nocfm_dir}", tag="main")


