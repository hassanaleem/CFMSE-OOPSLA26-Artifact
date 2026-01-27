import re
import subprocess
import psutil
import sys
import signal
import os
import time
DEBUG = True 

def debug_print(*args, tag="", **kwarg):
    if not DEBUG:
        return
    
    # print("DRIVER : ", end="")
    if tag != "":
        print(f"({tag}) : ", end="", flush=True)
    print(*args, **kwarg, flush=True)


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

def analyzeErroringTest(config, ktest_path, bitcode_path, error_location_data, klee_options):

    debug_print(f"Analyzing Erroring Test: {ktest_path}", tag="analyze")

    command = config['KLEE_BIN']() + " --replay-ktest-file=" + \
        ktest_path + f" {klee_options} " + bitcode_path + " " + str(config['PROG_ARGS'])

    debug_print("Executing : " + command, tag="analyze")
    process = subprocess.Popen(command, stderr=subprocess.PIPE, shell=True)
    error_detected = False

    while True:
        # Read a line from the subprocess's standard output
        output = process.stderr.readline()
        output_str = output.decode().strip()

        if b'KLEE: ERROR' in output:
            debug_print("Error detected when replaying test", tag="analyze")
            debug_print("KLEE OUTPUT " + output_str, tag="analyze")

            # check if error is the same error generated from given test or another error
            error_match = re.search(r'(\.\/.+):(\d+)', output_str)
            error_detected = True
            if error_match:
                file_name = error_match.group(1)
                line_number = error_match.group(2)
                if (file_name == error_location_data[0]) and (int(line_number) == int(error_location_data[2])):
                    error_detected = True
                else:
                    error_detected = False
        # If there's no more output, break the loop
        if output == b'' and process.poll() is not None:
            break

    debug_print(f"Detected error is a {'TRUE ERROR!' if error_detected else 'FALSE POSITIVE!'}", tag="analyze")
    
    # error_detected is true means its a true error
    return error_detected



def executeKleeWithoutTransformation(config, input_bitcode, process_start_time, klee_options):
    
    klee_command = f"{str(config['KLEE_BIN']())} {klee_options} {input_bitcode} {str(config['PROG_ARGS'])}"

    debug_print("Executing : " + klee_command, tag="klee-nocfm")
    # start a new process to execute KLEE
    process = subprocess.Popen(
        klee_command, stderr=subprocess.PIPE, stdout=subprocess.DEVNULL, shell=True)

    while True:
        # Read a line from the subprocess's standard output
        output = process.stderr.readline()
        output_str = output.decode().strip()

        debug_print(output_str, tag="klee-nocfm-stdout")

        if b'KLEE: ERROR: EXITING ON ERROR:' in output:
            error_time = time.time() - process_start_time
            debug_print(f"ERROR found in non-transformed KLEE run in {error_time} seconds!", tag="klee-nocfm")

        # If there's no more output, break the loop
        if output == b'' and process.poll() is not None:
            break

    debug_print("KLEE without CFM finished exploration", tag="klee-nocfm")

def keyboard_exit_handler(sig, frame):
    debug_print(f"\n\nKeyboardInterrupt (ID: {sig}) has been caught. Cleaning up...", tag="main")

    def kill_child_processes_recursive(parent_pid, sig=signal.SIGTERM):
        try:
            parent = psutil.Process(parent_pid)
        except psutil.NoSuchProcess:
            return
        children = parent.children(recursive=True)
        for process in children:
            process.send_signal(sig)

    debug_print("Killing all child processes...", tag="main")
    kill_child_processes_recursive(os.getpid())
    debug_print("Exiting...", tag="main")
    sys.exit(0)
  
def set_default( obj):
    if isinstance(obj, set):
        return list(obj)
    raise TypeError

class FalsePositiveDict:
    def __init__(self):
        self.dict = {}

    def addLocInfo(self, filename, funcname, lineno):
        if filename not in self.dict:
            self.dict[filename] = {}
        if funcname not in self.dict[filename]:
            self.dict[filename][funcname] = set()
        self.dict[filename][funcname].add(lineno)

    def hasLocInfo(self, filename, funcname, lineno):
        if filename not in self.dict:
            return False
        if funcname not in self.dict[filename]:
            return False
        if lineno not in self.dict[filename][funcname]:
            return False
        return True

    def size(self):
        return len(self.dict)

    def getDict(self):
        return self.dict
    

def parse_time_from_option_string(option_string):
    # look for substings of the form --max-time=[0-1]+[h|s]
    # and extract it into a tuple of (max_time, time_unit)
    # where time_unit is either 'h' or 's'
    # if no such substring is found, return None
    match = re.search(r"--max-time=([0-9]+)([h|s])", option_string)



    if not match:
        debug_print("Error: --max-time option not found in KLEE options!", tag="main")
        return None

    # if ths substring is found, remove the substring from the option string
    option_string = option_string.replace(match.group(0), "")

    # print("KLEE option string after removing --max-time option: " + option_string)

    max_time = int(match.group(1))
    time_unit = match.group(2)
    # print(f"Max time: {max_time} {time_unit}")

    # convert time to seconds
    if time_unit == 'h':
        max_time *= 3600

    # returns max time in seconds
    return [max_time, option_string]

# function to extract the program name from a path to .bc file
def get_prog_name_from_bc_path(bc_path):
    # get the file name from the path
    file_name = os.path.basename(bc_path)

    # remove the .bc extension from the file name
    prog_name = file_name.replace(".bc", "").split('/')[-1]

    if prog_name is None:
        return ""

    return prog_name
