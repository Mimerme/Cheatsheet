#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef char* string;
char* filename;

//Utility functions
int has_quickstart();

void compute_filepath(string);
void check_file(FILE*);
long get_file_size(FILE*);

void execute_process(string, string);
int count_chars(string, int, char);
void buffer_split(string, const char, string[]);
void parse_and_executes(string[], int, string);

//Commands accessible by the user
int quickstart();
void display_help();
void list_sheets(string args[]);

//  Commands that write to the file
void add_binary(int, string[]);
void add_sheets(int, string[]);
void show_sheet(int, string[]);
