#!python3

import sys
import getopt
import re


def main(argv):
    if len(argv) == 1:
        data = ""
        with open(argv[0], 'r') as file:
            data = file.read()
            data = "#include \"myMain.hpp\"\n"+data
            data = data.replace("/* Infinite loop */",
                                "myMain();")
        with open(argv[0],'w') as file:
            file.write(data)


if __name__ == "__main__":
    main(sys.argv[1:])
