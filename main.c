#include "hrk_shell.h"

void shell_loop(char** env) {
    char* input = NULL;
    size_t input_size = 0;
    char** args;

    while(true) {
        printf("[hrk-shell]>> ");

        if(getline(&input, &input_size, stdin) == -1) {
            //EOF or Ctrl+D
            perror("getline() interrupted or EOF");
            break;
        }
        args = parse(input);
        //below for loop is for testing purposes only
        for(size_t i = 0; args[i]; i++) {
            printf("Args: %s", args[i]);
            printf("\n");
        }
    }
}

int main(int argc, char** argv, char** env) {
    //we wont need argc and argv
    (void)argc;
    (void)argv;
    
    shell_loop(env);

    return 0;
}
