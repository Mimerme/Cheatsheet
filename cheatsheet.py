#!/bin/python3
import sys

def execute_process(binary_path, arguments):
    pass

def parse_and_execute():
    pass

def list_sheets(argv):
    pass

def display_help():
    pass

def show_sheet(argc, argv):
    pass

def add_sheet(argc, argv):
    pass

def add_binary(argc, argv):
    pass

def quickstart():
    pass

def main(argv):
    argc = len(argv)

    if argc == 1:
        print("No arguments specified")
        return
    
    if argv[1] == "list":
        list_sheets(argv)
    elif argv[1] == "help":
        display_help()
    elif argv[1] == "show":
        show_sheet(argc, argv)
    elif argv[1] == "add":
        add_sheet(argc, argv)
    elif argv[1] == "binary":
        add_binary(argc, argv)
    elif argv[1] == "quickstart":
        quickstart()
    else
        print("Unrecognized command. Type help for more information")


if __name__=='__main__':
    main(sys.argv)

