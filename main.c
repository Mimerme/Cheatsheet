#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef char* string;

struct string_split {
    string val;
    int size;
};

void execute_process(string bin_path, string file_path){
    char * new_str;
    new_str = malloc(strlen(bin_path) + strlen(file_path) + 1);
    strcat(new_str, bin_path);
    strcat(new_str, file_path);

    system(new_str);
}

long get_file_size(FILE *file){
   fseek(file, 0, SEEK_END);
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

void split(char *buffer, int buffer_offset, int line_size, struct string_split *split){
      string buffer_line = malloc(line_size * sizeof(char)); 

      //NOTE: Check these offsets
      memcpy(buffer_line, buffer + buffer_offset, line_size);
      //Splits
      split->val = buffer_line;
      split->size = line_size; 
}

//Splits a given buffer @ a given character into multiple strings
void buffer_split(char *buffer, int buff_size, char split_char, struct string_split splits[]){
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
        
        //If the character in the buffer is equal to the ASCII code, or if the character is null
        if(buff_char == split_char){
            split(buffer, buff_cursor, line_iter, &splits[current_split]); 
            current_split++;
            //Add an offset of 1 to skip over the newline char
            buff_cursor += line_iter + 1;
            line_iter = 0;
        }
        line_iter++;
    }

    //One final split @ the EOF
    split(buffer, buff_cursor, line_iter, &splits[current_split]); 
}

//Define the functions
void list_sheets(string args[]){
    const char* filename = ".sheets";

    //.sheets contains a mapping to all of the saved cheatsheets and their locations
    FILE *saved_sheets;
    //TODO: Check for file-perm bugs (may need to use r+)
    saved_sheets = fopen("./.sheets", "r"); 
    int file_size = get_file_size(saved_sheets);

    printf("Size of '.sheets' : %i bytes\n", file_size);
    
    char file_buffer[file_size];
    
    //Read all of the file's contents into a buffer and split the buffer at all of the newlines
    fread(file_buffer, sizeof(char), file_size, saved_sheets);
   
    int num_lines = count_chars(file_buffer, file_size, 10); 
    struct string_split splits[num_lines];
    buffer_split(file_buffer, file_size, 10, splits);
    

    const int spacing = 20;
    printf("%*s| %*s|%*s|\n", spacing,"Key Name", spacing, "File Location", spacing, "File Type");
    struct string_split colon_splits[3];
    for(int i = 0; i < num_lines; i++){
        //58 is the ASCII code for a colon
        buffer_split(splits[i].val, splits[i].size, 58, colon_splits);

        printf("%*s|%*s|%*s|\n", spacing, colon_splits[0].val, spacing, colon_splits[1].val, spacing, colon_splits[2].val);
    } 
    fclose(saved_sheets);
}

void add_sheets(int argc, string args[]){
    if(argc != 5){
        printf("Specifed %i parameters when there should be 3\n", argc - 2);
    }

    char *sheet_name = args[2];
    char *sheet_path = args[3];
    char *sheet_type = args[4];
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "a");
    
    fprintf(saved_sheets, "%s:%s:%s\n", sheet_name, sheet_path, sheet_type);

    fclose(saved_sheets);
}

void parse(string ){

}

void show_sheet(int argc, string args[]){
    if(argc != 3){
        printf("Specifed %i parameters when there should be 1\n", argc - 2);
        return;
    }
    
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "r");
 
    //Iterate over buffer
    int file_size;
    file_size = get_file_size(saved_sheets);
    char file_buffer[file_size];
    
    //Read all of the file's contents into a buffer and split the buffer at all of the newlines
    fread(file_buffer, sizeof(char), file_size, saved_sheets);
   
    int num_lines = count_chars(file_buffer, file_size, 10); 
    struct string_split splits[num_lines];
    buffer_split(file_buffer, file_size, 10, splits);
    

    string IMG_BIN, PDF_BIN, TXT_BIN, sheet_path;
   
    //Binaries must be kept in the first 3 lines 
    //[key]:[value]:[type]
    //Interate over each line until the key/bin paths are found
    for(int i = 0; i < num_lines; i++){
        struct string_split colon_splits[3];
        //58 is the ASCII code for a colon
        buffer_split(splits[i].val, splits[i].size, 58, colon_splits);

        //Parse line by line
        //Parse the binaries first
        if(strcmp(colon_splits[0].val, "IMG_BIN") == 0){
            IMG_BIN = colon_splits[1].val;
        }
        else if(strcmp(colon_splits[0].val, "PDF_BIN") == 0){
            PDF_BIN = colon_splits[1].val;
        }
        else if(strcmp(colon_splits[0].val, "TXT_BIN") == 0){
            TXT_BIN = colon_splits[1].val;
        }

        //Parse the files but check if the binaries have already been defined
        else if(strcmp(colon_splits[0].val, args[2]) == 0){
            sheet_path = colon_splits[1].val;
            if(strcmp(colon_splits[2].val, "img") == 0){
                if(IMG_BIN != NULL){
                    execute_process(IMG_BIN, sheet_path);
                }
                else{
                    printf("key <%s> was found, but <IMG_BIN> was not defined\n", colon_splits[0].val);
                }
            }
            else if(strcmp(colon_splits[2].val, "pdf") == 0){
                if(PDF_BIN != NULL){
                    execute_process(PDF_BIN, sheet_path);
                }
                else{
                    printf("key <%s> was found, but <PDF_BIN> was not defined\n", colon_splits[0].val);
                }
            }
            else if(strcmp(colon_splits[2].val, "txt") == 0){
                if(TXT_BIN != NULL){
                    execute_process(TXT_BIN, sheet_path);
                }
                else{
                    printf("key <%s> was found, but <TXT_BIN> was not defined\n", colon_splits[0].val);
                }
            }
            printf("The specified file type <%s> is unrecognized\n", colon_splits[2].val);
        }

        printf("Failed to find any sheets with the key : %s\n", args[2]);
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
            show_sheet(argc, argv);
            break;
        //add
        case 'a':
            add_sheets(argc, argv);
            break;
        default:
            printf("Unrecognized command. Type 'help' for more\n");
            break;
    }
}
