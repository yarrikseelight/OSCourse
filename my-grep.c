#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    //if not arguments are given do like instructed
    if (argc < 2){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    //save the word we're looking for
    char *inputString = argv[1];


    //if search term but no file is given
    if (argc == 2) {
        char *buffer = NULL;
        size_t buffsize = 0;

        while (getline(&buffer, &buffsize, stdin) != -1){
            //using strstr() to search for substring in larger string 
            //(help from https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm)
            if(strstr(buffer, inputString) != NULL){
                fputs(buffer, stdout);
            }     
        }
        free(buffer);
    }


    //loop through all the provided files
    for (int i = 2; i<argc; i++){
        //open file that's currently in turn in the for loop
        const char* filename = argv[i];
        FILE* file = fopen(filename, "r");

        //check files existence
        if (file == NULL) {
            fprintf(stderr, "my-grep: cannot open file\n");
            exit(1);

        //else loop through file line by line (help using getline() from https://www.youtube.com/watch?v=TKKQERrrt5o)
        } else {
            char *buffer = NULL;
            size_t buffsize = 0;

            while (getline(&buffer, &buffsize, file) != -1){
                //using strstr() to search for substring in larger string 
                //(help from https://www.tutorialspoint.com/c_standard_library/c_function_strstr.htm)
                if(strstr(buffer, inputString) != NULL){
                    fputs(buffer, stdout);
                } 
            }

            //close file and free buffer
            fclose(file);
            free(buffer);  
        }
    }
    return 0;
}