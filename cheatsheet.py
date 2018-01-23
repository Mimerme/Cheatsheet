#!/bin/python3
import sys
import shelve
import os
import subprocess
import platform

home_path = os.path.expanduser('~') + "/"
sheet_file = ".sheets"
sheet_file = home_path + sheet_file
quickstart_file = "Quickstart"
quickstart_file = home_path + quickstart_file

def execute_process(binary_path, arguments):
    return subprocess.call([binary_path, arguments])

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
    return 

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

    if(check_quickstart()):
        print("Bind a key to your new sheet...")
        
        process = subprocess.Popen(['xbindkeys', '-k'], stdout=subprocess.PIPE)
        stdout = process.communicate()[0]

        key = stdout.decode("utf-8").split('\n')[5]

        with open(home_path + "/.xbindkeysrc", 'a') as f:
            print(key)
            f.write("\n#" + argv[2] + "\n")
            f.write('\"sheemo show ' + argv[2] + "\"\n" + key)

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

def check_quickstart():
    return os.path.exists(quickstart_file) and os.path.isfile(quickstart_file)

def quickstart():
    if(platform.system() != "Linux"):
        print("Only Linux systems are supported")
        return

    xbindkey_ret = os.system("xbindkeys &> /dev/null")
    pqiv_ret = os.system("pqiv &> /dev/null")

    if(xbindkey_ret == 32512):
        print("xbindkeys not found")
    elif(xbindkey_ret != 0):
        print("Unknown error with xbindkeys")

    if(pqiv_ret == 32512):
        print("pqiv not found")
    elif(pqiv_ret != 0):
        print("Unknown error with pqiv")

    if(xbindkey_ret != 0 and pqiv_ret != 0):
        return

    if(check_quickstart()):
        print("Support for xbindkeys has already been enabled")
        return

    open(quickstart_file, "w+")
    print("Quickstart enabled!")

    return

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

