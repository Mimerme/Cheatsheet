#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

void execute_process(string bin_path, string file_path){

}

int strcicmp(char const *a, char const *b){
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

long get_file_size(FILE *file){
   fseek(file, 0L, SEEK_END);
   long size = ftell(file);
   rewind(file);
   return size; 
}

//Returns the number of characters in a given buffer
int count_chars(char *buffer, int buffer_length, char char_id){
    int count = 0;
    
    for(int i = 0; i < buffer_length; i++){
       if(buffer[i] == char_id){
            count++;
       } 
    }
    return count;
}


//Define the functions
void list_sheets(string args[]){
    const char* filename = ".sheets";

    //.sheets contains a mapping to all of the saved cheatsheets and their locations
    FILE *saved_sheets;
    //TODO: Check for file-perm bugs (may need to use r+)
    saved_sheets = fopen("./.sheets", "w+"); 
    long file_size = get_file_size(saved_sheets);

    printf("File Size of '.sheets' : %i \n", file_size);
    fclose(saved_sheets);
}

void add_sheets(string args[]){
    char *sheet_name = args[2];
    char *sheet_path = args[3];
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "a");
    
    fprintf(saved_sheets, "%s:%s\n", sheet_name, sheet_path);

    fclose(saved_sheets);
}

//Splits a given buffer @ a given character into multiple strings
void buffer_split(char *buffer, int buff_size, char split_char, string splits[]){
    //Points to the last position that the data was copied from (the last newline)
    short buff_cursor = 0;
    //Iterates over each character in the line until it runs into a newline
    //then adds to the buff_cursor and resets back to 0
    short line_iter = 0;
    char buff_char;

    //Split strings
    int current_split = 0;

    while(buff_cursor + line_iter < buff_size){
        buff_char = buffer[buff_cursor + line_iter];
        
        //If the character in the buffer is a newline
        if(buff_char == split_char){
            char buffer_line[line_iter];
            //NOTE: Check these offsets
            memcpy(buffer_line, buffer + buff_cursor, line_iter + 1);
            //Splits 
            splits[current_split] = buffer_line;

            current_split++;
            buff_cursor += line_iter;
            line_iter = 0;
        }
        line_iter++;
    }
}

void show_sheet(string args[]){
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "r");
 
    //Iterate over buffer
    long file_size;
    file_size = get_file_size(saved_sheets);
    char file_buffer[file_size];
    
    //Read all of the file's contents into a buffer and split the buffer at all of the newlines
    fread(file_buffer, sizeof(char), file_size, saved_sheets);
   
    int num_lines = count_chars(file_buffer, file_size, 10); 
    string splits[num_lines];
    buffer_split(file_buffer, file_size, 10, splits);
    
    char* IMG_BIN, PDF_BIN, TXT_BIN, sheet_path;
   
    //Binaries must be kept in the first 3 lines 
    //[key]:[value]:[type]
    //Interate over each line until the key/bin paths are found
    for(int i = 0; i < num_lines; i++){
        string colon_splits[3];
        //58 is the ASCII code for a colon
        buffer_split(splits[i], colon_splits, 58, colon_splits);

        //Get if the key = the requested
        if(strcicmp(colon_splits[0], args[2])){
            sheet_path = colon_splits[1];
            if(strcicmp(colon_splits[2], "img")){
                execute_process(IMG_BIN, sheet_path);
            }
            else if(strcicmp(colon_splits[2], "pdf")){
                execute_process(PDF_BIN, sheet_path);
            }
            else if(strcicmp(colon_splits[2], "txt")){
                execute_process(TXT_BIN, sheet_path);
            }
        } 
        else if(strcicmp(colon_splits[0], "IMG_BIN")){
            IMG_BIN = colon_splits[1];
        }
        else if(strcicmp(colon_splits[0], "PDF_BIN")){
            PDF_BIN = colon_splits[1];
        }
        else if(strcicmp(colon_splits[0], "TXT_BIN")){
            TXT_BIN = colon_splits[1];
        }
    } 


    //if any key chars are detected handle the buffer
    //take key value
    //search all new line breaks 
}

int main(int argc, string argv[]){
    if (argc == 1){
        printf("No arguments specified\n");
        return 0;
    }

    //Switch statement based on first character of second arg
    switch(argv[1][0]){
        //list
        case 'l':
            list_sheets(argv);
            break;
        //help
        case 'h':
            
            break;
        //show
        case 's':
            show_sheet(argv);
            break;
        //add
        case 'a':
            add_sheets(argv);
            break;
        default:
            printf("Unrecognized command. Type 'help' for more\n");
            break;
    }
}

