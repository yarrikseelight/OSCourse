//Originally has a decent solution but it assumed the line length so had to start over. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 10

int main(int argc, char *argv[]) {
    //if more than asked arguments print instructions
    if (argc > 3) {
        fprintf(stderr, "Usage: reverse <input> <output>\n");
        exit(1);
    }
    //User give no arguments (solution for arg==3 was written first this uses same solution but instead of input file we use stdin)
    else if (argc == 1){
        //use stdin as an inputfile
        FILE *readFile = stdin;

        //Creating lines to store the lines of the read file.
        char **lines = NULL;
        size_t line_count = 0;
        size_t current_capacity = INITIAL_CAPACITY; //current capacity is for how many lines can we hold (10 to begin with)

        // Allocating initial memory for lines array
        lines = malloc(current_capacity * sizeof(char *));
        if (lines == NULL) { 
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        char *buffer = NULL;
        size_t buffer_size = 0;
        size_t chars_read;

        //reading the lines (used ChatGPT to fix countless of errors and misunderstandings in this while loop)
        while ((chars_read = getline(&buffer, &buffer_size, readFile)) != -1) {
            if (line_count >= current_capacity) { //if line count exceed current capacity extend by 100%
                current_capacity *= 2;
                char **new_lines = realloc(lines, current_capacity * sizeof(char *));
                if (new_lines == NULL) {
                     fprintf(stderr, "realloc failed\n");
                     exit(1);
                }
                lines = new_lines; //update lines to point to the new extended memory
            }

            // Allocate memory for the current line and copy it
            lines[line_count] = malloc((chars_read + 1) * sizeof(char));
                if (lines[line_count] == NULL) {
                 fprintf(stderr, "malloc failed\n");
                 exit(1);
             }
            strcpy(lines[line_count], buffer);
            line_count++;
        }

        // Write lines in reverse order to screen (used help of ChatGPT for writing the lines in reverse)
        for (size_t i = line_count; i > 0; i--) {
            fprintf(stdout, "%s\n", lines[i - 1]);
        }

        
        // Free used memry slots
        free(buffer);
        for (size_t i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
        
        //Close all files 
        fclose(readFile);
        return 0;
        }


    //with input file only outputs to screen
    else if (argc == 2){
        //Open readfile
        FILE *readFile = fopen(argv[1], "r");
        if (readFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        //Creating lines to store the lines of the read file.
        char **lines = NULL;
        size_t line_count = 0;
        size_t current_capacity = INITIAL_CAPACITY; //current capacity is for how many lines can we hold (10 to begin with)

        // Allocating initial memory for lines array
        lines = malloc(current_capacity * sizeof(char *));
        if (lines == NULL) { 
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        char *buffer = NULL;
        size_t buffer_size = 0;
        size_t chars_read;

        //reading the lines (used ChatGPT to fix countless of errors and misunderstandings in this while loop)
        while ((chars_read = getline(&buffer, &buffer_size, readFile)) != -1) {
            if (line_count >= current_capacity) { //if line count exceed current capacity extend by 100%
                current_capacity *= 2;
                char **new_lines = realloc(lines, current_capacity * sizeof(char *));
                if (new_lines == NULL) {
                     fprintf(stderr, "realloc failed\n");
                     exit(1);
                }
                lines = new_lines; //update lines to point to the new extended memory
            }

            // Allocate memory for the current line and copy it
            lines[line_count] = malloc((chars_read + 1) * sizeof(char));
                if (lines[line_count] == NULL) {
                 fprintf(stderr, "malloc failed\n");
                 exit(1);
             }
            strcpy(lines[line_count], buffer);
            line_count++;
        }

        // Write lines in reverse order to screen (used help of ChatGPT for writing the lines in reverse)
        for (size_t i = line_count; i > 0; i--) {
            fprintf(stdout, "%s\n", lines[i - 1]);
        }

        
        // Free used memry slots
        free(buffer);
        for (size_t i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
        
        //Close all files 
        fclose(readFile);
        return 0;
    }

        
    //With input and outputfiles. Same as earlier but added write file. Double comments removed
    else if (argc == 3){
        //open readfile
        FILE *readFile = fopen(argv[1], "r");
        if (readFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }

        //Open writefile
        FILE *writeFile = fopen(argv[2], "w");
        if (writeFile == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            fclose(readFile);
            exit(1);
        }

        //check if input and output files are the same originally had just (readFile == writeFile) but it obviously caused bugs
        if (strcmp(argv[1], argv[2]) == 0){
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }

     

        //Creating lines to store the lines of the read file.
        char **lines = NULL;
        size_t line_count = 0;
        size_t current_capacity = INITIAL_CAPACITY; //current capacity is for how many lines can we hold (10 to begin with)
        // Allocating initial memory for lines array
        lines = malloc(current_capacity * sizeof(char *));
        if (lines == NULL) { 
            fprintf(stderr, "malloc failed\n");
            exit(1);
        }

        char *buffer = NULL;
        size_t buffer_size = 0;
        size_t chars_read;

       //reading the lines (used ChatGPT to fix countless of errors and misunderstandings in this while loop)
        while ((chars_read = getline(&buffer, &buffer_size, readFile)) != -1) {
            if (line_count >= current_capacity) { //if line count exceed current capacity extend by 100%
                current_capacity *= 2;
                char **new_lines = realloc(lines, current_capacity * sizeof(char *));
                if (new_lines == NULL) {
                     fprintf(stderr, "realloc failed\n");
                     exit(1);
                }
                lines = new_lines; //update lines to point to the new extended memory
            }

            // Allocate memory for the current line and copy it
            lines[line_count] = malloc((chars_read + 1) * sizeof(char));
                if (lines[line_count] == NULL) {
                 fprintf(stderr, "malloc failed\n");
                 exit(1);
             }
            strcpy(lines[line_count], buffer);
            line_count++;
        }

        // Write lines in reverse order to screen (used help of ChatGPT for writing the lines in reverse)
        for (size_t i = line_count; i > 0; i--) {
            fprintf(writeFile, "%s\n", lines[i - 1]);
        }
        
        // Free used memry slots
        free(buffer);
        for (size_t i = 0; i < line_count; i++) {
            free(lines[i]);
        }
        free(lines);
         
        //Close files
        fclose(readFile);
        fclose(writeFile);
        return 0;
        }
   
}
