#!/usr/bin/python3
import subprocess
import os
import re
import time
import multiprocessing
import psutil
import json
import signal
import sys
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from multiprocessing import Queue

DEBUG = True


def debug_print(*args, **kwargs):
    if DEBUG:
        print("DEBUG : ", end="")
        print(*args, **kwargs)


def getErrorLocationInformation(ktest_err_path):
    with open(ktest_err_path, "r") as f:
        data = f.read()

    # Get line number of error
    line_number = "all"  # default case if no line number is found
    line_number_match = re.search(r"Line: (\d+)", data)
    if line_number_match:
        line_number = line_number_match.group(1)

    # Get function causing error
    function_name = None
    stack_trace_match = re.search(r"Stack: \n((?:\t#[0-9]+ .+\n)+)", data)
    if stack_trace_match:
        stack_data = stack_trace_match.group(1)
        function_name_match = re.search(r"#\d+ in ([^(]+) ", stack_data)

        if function_name_match:
            function_name = function_name_match.group(1)

    # Get file causing error
    file_name = None
    file_path_match = re.search(r"File: (.+)", data)
    if file_path_match:
        file_path = file_path_match.group(1)
        # file_name = os.path.basename(file_path)
        file_name = file_path

    return (file_name, function_name, line_number)


def analyzeErroringTest(false_positive_objects_queue, execution_process_start_time, ktest_err_path, ktest_path, bitcode_path):
    # acquires the line number and function name of erroring test if exists
    error_location_data = getErrorLocationInformation(ktest_err_path)

    debug_print("Analyzing Erroring Test:", ktest_path)
    if DEBUG:
        # outputs failing test inputs
        subprocess.run([config['KTEST_BIN'](), ktest_path])

    command = config['KLEE_BIN']() + " --replay-ktest-file=" + \
        ktest_path + " " + bitcode_path + " " + str(config['PROG_ARGS'])

    debug_print("Executing : " + command)

    print("\033[1;35m", end="")
    print("KLEE replaying test ->", ktest_path, end="")
    print("\033[0m")
    process = subprocess.Popen(command, stderr=subprocess.PIPE, shell=True)
    error_detected = False

    while True:
        # Read a line from the subprocess's standard output
        output = process.stderr.readline()
        output_str = output.decode().strip()

        if b'KLEE: ERROR' in output:
            print("\033[1;31m", end="")
            print("KLEE: ERROR: In replaying erroring test!")
            print(output_str, end="")
            print("\033[0m")

            # check if error is the same error generated from given test or another error
            error_match = re.search(r'(\.\/.+):(\d+)', output_str)
            error_detected = True
            if error_match:
                file_name = error_match.group(1)
                line_number = error_match.group(2)
                if (file_name == error_location_data[0]) and (int(line_number) == int(error_location_data[2])):
                    error_detected = True
                    error_time = time.time() - execution_process_start_time
                    print("\033[1;31m", end="")
                    print("\nError found in seconds:", error_time, end="")
                    print("\033[0m")
                else:
                    error_detected = False
        # If there's no more output, break the loop
        if output == b'' and process.poll() is not None:
            break

    # return_code = process.poll()
    if (not error_detected):
        false_positive_object = (
            ktest_path, True, error_location_data[0], error_location_data[1], error_location_data[2])
        false_positive_objects_queue.put(false_positive_object)
        print("\033[1;32mErroring Test is a false positive ->",
              ktest_path, end="")
        print("\033[0m")
    else:
        false_positive_object = (
            ktest_path, False, error_location_data[0], error_location_data[1], error_location_data[2])
        false_positive_objects_queue.put(false_positive_object)
        print("\033[1;31mErroring Test is a real error ->", ktest_path, end="")
        print("\033[0m")


class TestDirectoryHandler(FileSystemEventHandler):
    def __init__(self, process_queue, false_positive_objects_queue, execution_process_start_time, bitcode_path):
        super().__init__
        self.main_test_output_directory = ""
        self.process_queue = process_queue
        self.false_positive_objects_queue = false_positive_objects_queue
        self.execution_process_start_time = execution_process_start_time
        self.bitcode_path = bitcode_path

    def on_any_event(self, event):
        if event.event_type == 'modified':
            if (".err" in event.src_path):  # if an erroring test case has been made
                test_output_directory = os.path.dirname(event.src_path)
                if (self.main_test_output_directory == "" or self.main_test_output_directory == test_output_directory):
                    debug_print(f"Erroring Test is: {event.src_path}")
                match = re.search(r"test\d{6}", event.src_path)
                if match:
                    test_number = match.group(0)
                    ktest_err_path = event.src_path
                    test_directory = os.path.dirname(
                        test_output_directory) + "/"

                    # analyze if error is a false positive
                    if (self.main_test_output_directory == "" or self.main_test_output_directory == test_output_directory):
                        new_process = multiprocessing.Process(target=analyzeErroringTest, args=(
                            self.false_positive_objects_queue, self.execution_process_start_time, ktest_err_path, test_output_directory + "/" + test_number + ".ktest", self.bitcode_path))
                        new_process.start()  # run false positive error analysis on different process
                        self.process_queue.put(new_process.pid)
                        self.main_test_output_directory = test_output_directory
                else:
                    print("No match found")


def executeKleeWithoutTransformation(input_bitcode, output_dir, process_start_time):
    print(f"Running KLEE without CFM inside {output_dir}")
    klee_command = f"{str(config['KLEE_BIN']())} {str(config['KLEE_OPTIONS'])} --output-dir={output_dir} {input_bitcode} {str(config['PROG_ARGS'])}"

    debug_print("Executing : " + klee_command)
    # start a new process to execute KLEE
    process = subprocess.Popen(
        klee_command, stderr=subprocess.PIPE, shell=True)

    while True:
        # Read a line from the subprocess's standard output
        output = process.stderr.readline()
        output_str = output.decode().strip()

        debug_print(output_str)

        if b'KLEE: WARNING' in output:
            debug_print("\033[1;35m", end="")
            debug_print(output_str, end="")
            debug_print("\033[0m")

        if b'KLEE: ERROR' in output:
            error_time = time.time() - process_start_time
            print("\033[1;31m", end="")
            print("KLEE: ERROR: In non-transformed KLEE execution!")
            print(output_str, end="")
            print("\nError found in seconds:", error_time, end="")
            print("\033[0m")

        if b'KLEE: done:' in output:
            debug_print("\033[1;32m", end="")
            debug_print(output_str, end="")
            debug_print("\033[0m")

        # If there's no more output, break the loop
        if output == b'' and process.poll() is not None:
            break

    # Get the subprocess's return code
    return_code = process.poll()

    # Print the return code
    if (return_code == 0):
        print(
            "\033[1;32mSymbolic execution WITHOUT transformation finished successfully", end="")
        print("\033[0m")
    else:
        print(
            "\033[1;31mSymbolic execution WITHOUT transform failed!", end="")
        print("\033[0m")


def keyboard_exit_handler(sig, frame):
    print(f"\n\nKeyboardInterrupt (ID: {sig}) has been caught. Cleaning up...")

    def kill_child_processes_recursive(parent_pid, sig=signal.SIGTERM):
        try:
            parent = psutil.Process(parent_pid)
        except psutil.NoSuchProcess:
            return
        children = parent.children(recursive=True)
        for process in children:
            process.send_signal(sig)

    print("Killing all child processes...")
    kill_child_processes_recursive(os.getpid())
    print("Exiting...")
    sys.exit(0)


# Register the signal handler for SIGINT signal
signal.signal(signal.SIGINT, keyboard_exit_handler)


def run_main(input_bitcode, config_, run_in_dir):

    # set the global config variable
    global config
    config = config_

    process_start_time = time.time()

    # if run_in_dir does not exist, print error and exit
    if not os.path.isdir(run_in_dir):
        print(f"Error: {run_in_dir} does not exist!")
        sys.exit(1)

    # if run_in_dir is not an abosolute path, make it an absolute path
    if not os.path.isabs(run_in_dir):
        run_in_dir = os.path.abspath(run_in_dir)

    # if input_bitcode file does not exist, print error and exit
    if not os.path.isfile(input_bitcode):
        print(f"Error: {input_bitcode} does not exist!")
        sys.exit(1)

    # if input_bitcode is not an abosolute path, make it an absolute path
    if not os.path.isabs(input_bitcode):
        input_bitcode = os.path.abspath(input_bitcode)

    # get current epoch time
    current_epoch_time = int(time.time())
    # create klee-cfm-run-<epoch-time> and klee-nocfm-<epoch-time> directories
    klee_cfm_dir = os.path.join(
        run_in_dir, "klee-cfm-run-" + str(current_epoch_time))
    klee_nocfm_dir = os.path.join(
        run_in_dir, "klee-nocfm-" + str(current_epoch_time))

    print(f"Running klee without the transformation on {input_bitcode}")
    klee_without_transform_process = multiprocessing.Process(
        target=executeKleeWithoutTransformation, args=(input_bitcode, klee_nocfm_dir, process_start_time))
    klee_without_transform_process.start()

    re_execute_klee_with_transformation = True
    false_positives_information = {}
    execution_process_start_time = None

    execution_process_start_time = time.time()

    while re_execute_klee_with_transformation:
        # Execute KLEE with transformation on program
        klee_with_cfm_options = str(
            config['KLEE_OPTIONS']) + " " + str(config['CFM_OPTIONS'])

        if not false_positives_information:  # no false positives so far
            command = f"{str(config['KLEE_BIN']())} {klee_with_cfm_options} --output-dir={klee_cfm_dir} {input_bitcode} {str(config['PROG_ARGS'])}"
        else:
            command = f"{str(config['KLEE_BIN']())} {klee_with_cfm_options} -klee-cfmse-dont-touch-locs={str(config['CFMSE_IGNORE_JSON'])} --output-dir={klee_cfm_dir} {input_bitcode} {str(config['PROG_ARGS'])}"

        debug_print("Executing : " + command)

        process = subprocess.Popen(
            command, stderr=subprocess.PIPE, shell=True)

        # wait until klee_cfm_dir is created
        while not os.path.isdir(klee_cfm_dir):
            # sleep for 1 ms
            time.sleep(0.001)

        # start a process to detect when files get added/changed
        process_queue = Queue()
        false_positive_objects_queue = Queue()
        observer = Observer()

        event_handler = TestDirectoryHandler(
            process_queue, false_positive_objects_queue, execution_process_start_time, input_bitcode)
        observer.schedule(event_handler, klee_cfm_dir, recursive=True)
        observer.start()

        while True:
            # Read a line from the subprocess's standard output
            output = process.stderr.readline()
            output_str = output.decode().strip()

            debug_print(output_str)

            if b'KLEE: WARNING' in output:
                debug_print("\033[1;35m", end="")
                debug_print(output_str, end="")
                debug_print("\033[0m")

            if b'KLEE: ERROR' in output:
                error_time = time.time() - execution_process_start_time
                print("\033[1;31m", end="")
                print("KLEE: ERROR: In transformed KLEE execution!")
                print("Error found in " + str(error_time) + " seconds")
                print(output_str, end="")
                print("\033[0m")

            if b'KLEE: done:' in output:
                print("\033[1;32m", end="")
                print(output_str, end="")
                print("\033[0m")

            # If there's no more output, break the loop
            if output == b'' and process.poll() is not None:
                break

        # Get the subprocess's return code
        return_code = process.poll()

        # Print the return code
        if (return_code == 0):
            print(
                "\033[1;32mSymbolic execution with CFM finished successfully", end="")
            print("\033[0m")
        else:
            print(
                "\033[1;31mSymbolic execution with transform failed!", end="")
            print("\033[0m")

        # waits for all false positive checking process to finish before moving to next test
        while not process_queue.empty():
            process_id = process_queue.get()
            try:
                process = psutil.Process(process_id)
                process.wait()
            except:
                pass

        # checks for any new false positives found from false positive error analysis
        new_false_positives = []
        while not false_positive_objects_queue.empty():
            false_positive_object = false_positive_objects_queue.get()
            debug_print(false_positive_object)
            # if erroring test is a false positive
            if (false_positive_object[1] == True):
                new_false_positives.append(false_positive_object)

        observer.stop()
        observer.join()

        # new_false_positive format (ktest_path, isFalsePositive, error_file_name, error_function_name, error_line_number)
        # following block appends new found false positives to false positive dictionary
        for new_false_positive in new_false_positives:
            file_name = new_false_positive[2]
            if file_name in false_positives_information:
                function_name = new_false_positive[3]
                if function_name in false_positives_information[file_name]:
                    error_line_number = new_false_positive[4]
                    if false_positives_information[file_name][function_name] != "all":
                        if error_line_number == "all":
                            false_positives_information[file_name][function_name] = "all"
                        else:
                            false_positives_information[file_name][function_name].append(
                                int(error_line_number))
                else:
                    error_line_number = new_false_positive[4]
                    if error_line_number == "all":
                        false_positives_information[file_name][function_name] = "all"
                    else:
                        false_positives_information[file_name][function_name] = [
                            int(error_line_number)]
            else:
                function_name = new_false_positive[3]
                error_line_number = new_false_positive[4]
                if error_line_number == "all":
                    false_positives_information[file_name] = {
                        function_name: "all"}
                else:
                    false_positives_information[file_name] = {
                        function_name: [int(error_line_number)]}

        debug_print(false_positives_information)

        # dumps false positive location information to json so klee can use in next iteration
        with open(config["CFMSE_IGNORE_JSON"], "w") as outfile:
            json.dump(false_positives_information, outfile)

        # if no false positives were found on run, terminate loop and move to next test
        if len(new_false_positives) == 0:
            re_execute_klee_with_transformation = False
        else:
            print("\033[1;35m", end="")
            print(
                "KLEE re-executing to remove false positves", end="")
            print("\nUsing false positive locations information ->",
                  false_positives_information, end="")
            print("\033[0m")

    if klee_without_transform_process.is_alive():
        print("\033[1;35m", end="")
        print(
            "Waiting for KLEE without Transformation to finish execution", end="")
        print("\033[0m")
    klee_without_transform_process.join()


# if __name__ == "__main__":
#     input_bitcode_file = sys.argv[1]
#     run_in_dir = sys.argv[2]
#     run_main(input_bitcode_file, " ", run_in_dir)
