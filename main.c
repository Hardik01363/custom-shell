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
    }
}

int main(int argc, char** argv, char** env) {
    //we wont need argc and argv
    (void)argc;
    (void)argv;
    
    shell_loop(env);

    return 0;
}
