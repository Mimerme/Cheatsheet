# Define required macros here
SHELL = /bin/sh

SOURCE_FILES = sheemo.py
CC = python3
INSTALL_PATH=/usr/local/bin/
BIN_NAME=sheemo

INSTALL_PATH:=${INSTALL_PATH}${BIN_NAME}

release:
	@echo Compiling release
	${CC} -m ${SOURCE_FILES}

install: release
	@echo Installing 'cheatsheet' as ${INSTALL_PATH}
	@sudo mv a.out ${INSTALL_PATH}

clean:
	-rm -f *.out
