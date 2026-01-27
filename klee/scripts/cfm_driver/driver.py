import json
import os
import sys
import optparse as op
from core_exit_on_error import run_main_exit_on_error, debug_print
from core_noexit_on_error import run_main_noexit_on_error

# global config
config = {
    'KLEE_BUILD_DIR': os.environ['KLEE_BUILD_DIR'],
    'LLVM_BUILD_DIR': os.environ['LLVM_BUILD_DIR'],
    'KLEE_BIN': lambda: config['KLEE_BUILD_DIR'] + "/bin/klee",
    'KTEST_BIN': lambda: config['KLEE_BUILD_DIR'] + "/bin/ktest-tool",
    'CFMSE_IGNORE_JSON': "cfmse_ignore.json",
    'KLEE_OPTIONS' : "--max-memory=51200 --max-time=1h --only-output-states-covering-new --write-cov",
    'CFM_OPTIONS' : "-klee-cfmse -klee-cfmse-loads-symbolic",
    'PROG_ARGS' : ""
}

def main():
    # define an option parser
    parser = op.OptionParser()
    # option to take input bitcode file
    parser.add_option("-i", "--input-bc", dest="input_bc", help="Input bitcode file")
    # option to take klee options file
    parser.add_option("-k", "--klee-options-json", dest="klee_options_json", help="Klee options file")
    # option for run-on directory
    parser.add_option("-r", "--run-in-dir", dest="run_in_dir", help="Run on directory")
    # option for a dry run
    parser.add_option("-d", "--dry-run", dest="dry_run", action="store_true", help="Print the config and exit")
    # options to use exit on error
    parser.add_option("-e", "--exit-on-error", dest="exit_on_error", action="store_true", help="Exit on error")

    # parse the options
    (options, args) = parser.parse_args()


    # if input bitcode file is not provided then exit
    if not options.input_bc:
        debug_print("Input bitcode file not provided", tag="main")
        sys.exit(1)
    
    # if klee options file is not provided then exit
    if not options.klee_options_json:
        debug_print("KLEE options json not provided", tag="main")
        sys.exit(1)

    # if run-on directory is not provided then use the current directory
    if not options.run_in_dir:
        options.run_in_dir = os.getcwd()

    # check if the run_in_dir exists
    if not os.path.exists(options.run_in_dir):
        debug_print("Run-on directory does not exist", tag="main")
        sys.exit(1)

    # read the klee options json
    with open(options.klee_options_json, 'r') as f:
        klee_options = json.load(f)
        
        if 'KLEE_OPTIONS' in klee_options:
            debug_print("Overriding KLEE_OPTIONS", tag="main")
            config['KLEE_OPTIONS'] = klee_options['KLEE_OPTIONS']
        if 'CFM_OPTIONS' in klee_options:
            debug_print("Overriding CFM_OPTIONS", tag="main")
            config['CFM_OPTIONS'] = klee_options['CFM_OPTIONS']

        if 'PROG_ARGS' in klee_options:
            config['PROG_ARGS'] = klee_options['PROG_ARGS']

    debug_print("Runnign CFMSE driver with follwing options:", tag="main")
    print("-------------------------------------------")
    print("Input bitcode file\t: {}".format(options.input_bc))
    print("Program arguments\t: {}".format(config['PROG_ARGS']))
    print("KLEE options\t\t: {}".format(config['KLEE_OPTIONS']))
    print("CFM options\t\t: {}".format(config['CFM_OPTIONS']))
    print("Run on directory\t: {}".format(options.run_in_dir))
    print("-------------------------------------------")

    if options.dry_run:
        
        if options.exit_on_error:
            run_main_exit_on_error(options.input_bc, config, options.run_in_dir, dry_run=True)
        else:
            run_main_noexit_on_error(options.input_bc, config, options.run_in_dir, dry_run=True)

        debug_print("Dry run requested. Exiting", tag="main")
        sys.exit(0)

    # run the driver
    if options.exit_on_error:
        run_main_exit_on_error(options.input_bc, config, options.run_in_dir)
        return

    debug_print("no exit on error is not maintained!!!", tag="main")
    # run_main_noexit_on_error(options.input_bc, config, options.run_in_dir)
    return 
    

if __name__ == '__main__':
    main()