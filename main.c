#include "hrk_shell.h"

int shell_builts(char** args, char** env, char* init_dir) {
    
}

void shell_loop(char** env) {
    char* input = NULL;
    size_t input_size = 0;
    char** args;
    char* init_dir = getcwd(NULL, 0); //initialising a directory

    while(true) {
        printf("[hrk-shell]>> ");

        if(getline(&input, &input_size, stdin) == -1) {
            //EOF or Ctrl+D
            perror("getline() interrupted or EOF");
            break;
        }
        args = parse(input);
        //below for loop is for testing purposes only
        //for(size_t i = 0; args[i]; i++) {
        //    printf("Args: %s", args[i]);
        //    printf("\n");
        //}
        
        if(!args[0]) { //Note to self: Check if args[0] would work
            shell_builts(args, env, init_dir);
        }
    }
    free_tokens_memory(args);
}

int main(int argc, char** argv, char** env) {
    //we wont need argc and argv, but, need env, so, both these have been input as arguments so that we are able to input the env argument
    (void)argc;
    (void)argv;
    
    shell_loop(env);

    return 0;
}
