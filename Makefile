# Define required macros here
SHELL = /bin/sh

SOURCE_FILES =  main.c
CC = gcc
INSTALL_PATH=/usr/local/bin/
BIN_NAME=cheatsheet

INSTALL_PATH:=${INSTALL_PATH}${BIN_NAME}

release:
	echo Compiling release
	${CC} ${SOURCE_FILES}

debug:	
	echo Compiling debug
	${CC} -g ${SOURCE_FILES}

install: release
	echo ${INSTALL_PATH}
	sudo mv a.out ${INSTALL_PATH}

clean:
	-rm -f *.out
