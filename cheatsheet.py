#!/bin/python3
import sys
import shelve
import os
import subprocess

home_path = os.path.expanduser('~') + "/"
sheet_file = ".sheets"
sheet_file = home_path + sheet_file

def execute_process(binary_path, arguments):
    subprocess.call([binary_path, arguments])
    return

def list_sheets(argv):
    row_format ="{:^15}|{:^15}|{:^15}"
    row = row_format.format("FileID", "Path", "Type")
    print(row)
    print("------------------------------------------")

    with shelve.open(sheet_file) as sheets:
        for key in sheets:
            row = row_format.format(key, sheets[key]['path'], sheets[key]['type'])
            print(row)
    return

def display_help():
    print("--Help Menu--\n\
            list - list the saved sheets\n\
            help - display this help menu\n\
            show - display a sheet with its specifed binary\n\
            add - save a new sheet\n\
            bin - add a new binary to open a specific file type\n\
            quick - configure quickstart\n")
    pass

def show_sheet(argc, argv):
    if argc != 3:
        print("Specified " + str(argc - 2)  + " parameters when there should be 1")
        return
    
    file_id = argv[2]

    #Parse & execute the program
    with shelve.open(sheet_file) as sheets:
        #First iterate to to find the key
        for sheet in sheets:
            if(sheet == file_id):
                file_type = sheets[sheet]['type']

                #Then iterate to find the corresponding binary
                for binary in sheets:
                    if binary == file_type and sheets[binary]['type'] == 'bin':
                        execute_process(sheets[binary]['path'], sheets[sheet]['path'])


    return

def add_sheet(argc, argv):
    if argc != 5:
        print("Specified " + str(argc - 2)  + " parameters when there should be 3")
        return

    with shelve.open(sheet_file) as sheets:
        sheets[argv[2]] = {'path': argv[3], 'type': argv[4]}
    return

def add_binary(argc, argv):
    if argc != 4:
        print("Specified " + str(argc - 2)  + " parameters when there should be 2")
        return

    with shelve.open(sheet_file) as sheets:
        sheets[argv[2]] = {'path': argv[3], 'type': 'bin'}
    return

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
    else:
        print("Unrecognized command. Type help for more information")


if __name__=='__main__':
    main(sys.argv)

