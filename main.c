#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef char* string;

void execute_process(string bin_path, string file_path){
    char * new_str;
    new_str = malloc(strlen(bin_path) + strlen(file_path) + 1);
    strcat(new_str, bin_path);
    strcat(new_str, " ");
    strcat(new_str, file_path);

    system(new_str);
    free(new_str);
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

//Splits a given buffer @ a given character into multiple strings
void buffer_split(char *buffer, const char split_char, string splits[]){
    int i = 0;
    string split;

    while((split = strsep(&buffer, &split_char)) != NULL){  
        int length = strlen(split);

        splits[i] = malloc(length * sizeof(char));
        memcpy(splits[i], split, length);
        i++;
    }
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
    string splits[num_lines];
    buffer_split(file_buffer, 10, splits);
    

    const int spacing = 20;
    printf("%*s| %*s|%*s|\n", spacing,"Key Name", spacing, "File Location", spacing, "File Type");
    string colon_splits[3];
    
    //Avoid segfaulting
    colon_splits[1] = "";
    colon_splits[2] = "";

    for(int i = 0; i < num_lines; i++){
        //58 is the ASCII code for a colon
        buffer_split(splits[i], 58, colon_splits);
        //Filter out the binaries
        if(strcmp(colon_splits[2], "bin") == 0 || strcmp(colon_splits[2], "") == 0)
            continue; 

        printf("%*s|%*s|%*s|\n", spacing, colon_splits[0], spacing, colon_splits[1], spacing, colon_splits[2]);
    } 
    fclose(saved_sheets);
}

void add_binary(int argc, string args[]){
    if(argc != 4){
        printf("Specifed %i parameters when there should be 3\n", argc - 2);
        return;
    }

    char *binary_location = args[2];
    char *binary_type = args[3];
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "a");
    
    fprintf(saved_sheets, "%s:%s:bin\n", binary_type, binary_location);

    fclose(saved_sheets);
   
}

void add_sheets(int argc, string args[]){
    if(argc != 5){
        printf("Specifed %i parameters when there should be 3\n", argc - 2);
        return;
    }

    char *sheet_name = args[2];
    char *sheet_path = args[3];
    char *sheet_type = args[4];
    FILE *saved_sheets;
    saved_sheets = fopen("./.sheets", "a");
    
    fprintf(saved_sheets, "%s:%s:%s\n", sheet_name, sheet_path, sheet_type);

    fclose(saved_sheets);
}

void parse_and_execute(string lines[], int num_lines, string key){
    for(int i = 0; i < num_lines; i++){
        string colon_splits[3];
        colon_splits[1] = "";
        colon_splits[2] = "";

        buffer_split(lines[i], 58, colon_splits);
        string file_type, file_location;

        if(strcmp(colon_splits[0], key) == 0){
            //Save some of the array into temporary variables
            file_type = malloc(strlen(colon_splits[2]) * sizeof(char));
            file_type = colon_splits[2];

            file_location = malloc(strlen(colon_splits[1]) * sizeof(char));
            file_location = colon_splits[1];

            //Iterate over the file buffer again and find the binaries
            for(int k = 0; k < num_lines; k++){
                buffer_split(lines[k], 58, colon_splits);
                if(strcmp(colon_splits[0], file_type) == 0 && strcmp(colon_splits[2], "bin") == 0){
                    execute_process(colon_splits[1], file_location); 
                    return;
                }
            }
            printf("sheet was found, but its corresponding binary was not defined\n");
            free(file_type);
            free(file_location);
            return;
        }
    }
    printf("No sheet was found corresponding to the given key\n");
    return;
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
    string splits[num_lines];
    buffer_split(file_buffer, 10, splits);
    
    parse_and_execute(splits, num_lines, args[2]);
}

void display_help(){
    //TODO: Write a help menu
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
            display_help(); 
            break;
        //show
        case 's':
            show_sheet(argc, argv);
            break;
        //add
        case 'a':
            add_sheets(argc, argv);
            break;
        //add binary
        case 'b':
            add_binary(argc, argv);
            break;
        default:
            printf("Unrecognized command. Type 'help' for more\n");
            break;
    }
}
