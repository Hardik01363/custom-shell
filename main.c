#include "hrk_shell.h"

int shell_builtins(char** args, char** env, char* init_dir) {
    if(my_strcmp(args[0], "pwd") == 0) {return cmd_pwd();}
    else if(my_strcmp(args[0], "cd") == 0) {return cmd_cd(args, init_dir);}
    else if(my_strcmp(args[0], "which") == 0) {return cmd_which(args, env);}
    else if(my_strcmp(args[0], "echo") == 0) {return cmd_echo(args, env);}
    else if(my_strcmp(args[0], "env") == 0) {return cmd_env(env);}
    else if(my_strcmp(args[0], "exit") == 0 || my_strcmp(args[0], "quit") == 0 || my_strcmp(args[0], "q") == 0) {exit(EXIT_SUCCESS);}
    else {//not a built-in command
        //executor();        
    }
    return 0; //only temporary till else statement is left empty
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

        if(!args[0]) {return;}
        else if(my_strcmp(args[0], "setenv") == 0) {
            env = cmd_setenv(args, env);
        }
        else if(my_strcmp(args[0], "unsetenv") == 0) {
            env = cmd_unsetenv(args, env);
        }
        else {
            shell_builtins(args, env, init_dir);
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
