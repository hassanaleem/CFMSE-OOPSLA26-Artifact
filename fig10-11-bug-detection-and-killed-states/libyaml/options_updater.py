import json
import sys

def update_driver_options(size):
    with open('driver_options.json', 'r') as f:
        options = json.load(f)

    options['PROG_ARGS'] = f" {size} "

    with open('driver_options.json', 'w') as f:
        json.dump(options, f, indent=4)
def main():
    size = sys.argv[2]
    update_driver_options(size)

if __name__ == "__main__":
    main()