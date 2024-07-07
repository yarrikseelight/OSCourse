#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    //check that at least one file is given
    if (argc < 2) {
        exit(0);
    }

    //loop through all the provided files
    for (int i = 1; i<argc; i++){
        //open file that's currently in turn in the for loop
        const char* filename = argv[i];
        FILE* file = fopen(filename, "r");

        //check files existence
        if (file == NULL) {
            fprintf(stderr, "my-cat: cannot open file\n");
            exit(1);

        //else loop through file and output every character
        //help for looping was got from "Portfolio Courses" Youtube channel: https://www.youtube.com/watch?v=fLPqn026DaE
        } else {
            char c; 
            while ((c=fgetc(file)) != EOF) {
                 fprintf(stdout, "%c", c);
            }

            //add \n to separate file contents from each others
            fprintf(stdout, "\n");


            //close file
            fclose(file);
            
        }
    }
    return 0;
};




