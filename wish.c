#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


char *search_paths[50];
int num_paths = 1; // Start with one default path: /bin
char error_message[30] = "An error has occurred\n";

//function to refresh the search paths array
void free_paths() {
    for (int i = 0; i < num_paths; i++) {
        free(search_paths[i]);
    }
    num_paths = 0;
}


//handle build in commands
int builtin_commands(char *tokens[], int index){
        if (strcmp(tokens[0], "exit") == 0){
            if(index != 1){
                write(STDERR_FILENO, error_message, strlen(error_message)); 
                return 1; 
            }
            exit(0);
        } else if (strcmp(tokens[0], "cd") == 0){
            if(chdir(tokens[1]) != 0){
                write(STDERR_FILENO, error_message, strlen(error_message)); 
                return 1;
            }
        } else if (strcmp(tokens[0], "path") == 0){
                free_paths();
                num_paths = 0;
            if (index>1){
                for (int i = 1; i < index; i++) {
                    if (i >= 50) {
                        write(STDERR_FILENO, error_message, strlen(error_message));
                        return 1;
                }
                search_paths[num_paths++] = strdup(tokens[i]);
            }
            }
        } else {
            return 0;
        }
        return 1;
}

//function to execute the non builtin commands
void exec(char *tokens[]){
    //See if fork is succesful (=0) if yes continue to execute
        //help for for from https://www.geeksforgeeks.org/fork-system-call/
        pid_t p = fork(); //creating a child process
        if (p < 0){ //if not succesful
            write(STDERR_FILENO, error_message, strlen(error_message));    
        } else if (p == 0){ //if child process creation succesful --> execute
            for (int i = 0; i < num_paths; i++) { //loop through searchpaths and search for given executable

                char command_path[1024]; //this and next line was given by ChatGPT I tried to access in the loop just search_paths[i] but it didn't work 
                snprintf(command_path, sizeof(command_path), "%s/%s", search_paths[i], tokens[0]);

                //if we find the executable use execv to execute it 
                if (access(command_path, X_OK) == 0){
                    execv(command_path, tokens);
                }
            } 
            write(STDERR_FILENO, error_message, strlen(error_message));
            exit(1);
        } else {
            wait(NULL);
        }
};


//interactive mode
void interactive_mode() {
    char *command = NULL;
    size_t size = 0;
    size_t user_command;
    
    
    while(1){
        printf("wish> ");
        user_command = getline(&command, &size, stdin);
        //printf("%s", command);

        //removing the newline character for strcmp to recognise "exit" (caused bugs) 
        if (command[user_command - 1] == '\n') {
                command[user_command - 1] = '\0';
            }

        //tokenize input (help from https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm)
        const char separator[2] = " ";
        char *token;
        char *tokens[100];
        int index = 0;

        //tokenize the command and save each token in tokens[]
        token = strtok(command,separator);
        while( token != NULL ) {
            tokens[index++] = token;
            token = strtok(NULL, separator);
        }
        tokens[index] = NULL;

        if (index == 0) {
            continue;
        }

        //handle built in commands
        // builtin_commands(tokens,index);  
        bool x = builtin_commands(tokens, index);
        if (!x){
            exec(tokens);
        }     
    }
}

void batch_mode(char *filename){
    FILE *file = fopen(filename, "r");
    if (!file) {
        write(STDERR_FILENO, error_message, strlen(error_message));
        exit(1);
    }

    printf("(wish>) ");
    //UNFINISHED
}





int main(int argc, char *argv[]) {
    //initialize default paths using strdup to prevent errors that occured with just a string.
    search_paths[0] = strdup("/bin");

    //interacrtive mode
    if (argc == 1){
    interactive_mode();
   }
   //batchmode
   else if (argc == 2){
    batch_mode(argv[1]);
   }
   
free_paths();
return(0);
}
