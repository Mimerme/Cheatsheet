# Define required macros here
SHELL = /bin/sh

SOURCE_FILES =  main.c
CC = gcc

hello:
	${CC} ${SOURCE_FILES}

debug:
	${CC} -g ${SOURCE_FILES}

clean:
	-rm -f *.out
