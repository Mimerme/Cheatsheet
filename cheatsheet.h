#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef char* string;
char* filename;

void compute_filepath(string file);
void check_file(FILE* file);
int has_quickstart();
void execute_process();
long get_file_size(FILE* file);
int count_chars(string buffer, int buffer_length, char char_id);
void buffer_split(string buffer, const char split_char, string splits[]);
void list_sheets(string args[]);
void add_binary(int argc, string args[]);
int quickstart();
void add_sheets(int argc, string args[]);
void parse_and_executes(string lines[], int num_lines, string key);
void show_sheet(int argc, string args[]);
void display_help();
