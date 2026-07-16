#include "hrk_shell.h"

int cmd_pwd() {
    char* cwd = NULL;
    cwd = getcwd(NULL, 0); //Memory allocated dynamically (will free later)
    if(cwd != NULL) {
        printf("%s\n", cwd);
        free(cwd);
    }
    else {
        perror("pwd: getcwd failed");
    }
    return 0;
}

int cmd_cd(char** args, char* init_dir) {
    if(args[1] == NULL) {
        printf("cd: expected argument - cd [path-to-dir/file]\n");
    }
    else if(chdir(args[1]) == 0) {
        printf("cd: cd completed as intended\n");
    }
    else{
        perror("CD");
    }
    return 0;
}

int cmd_env(char** env) {
    size_t i = 0;
    while(env[i]) {printf("%s\n", env[i]); i++;}
    return 0;
}

int cmd_which(char** args, char** env) {
    if(args[1] == NULL) {
        printf("which: expected argument\n");
        return 1;
    }
    //list of builtin commands available to search with which command
    const char* builtin_cmds[] = {"pwd", "cd", "env", "setenv", "unsetenv", "which", "echo", "exit"};
    for(size_t i = 0; builtin_cmds[i]; i++) {
        if(my_strcmp(builtin_cmds[i], args[1]) == 0) {
            printf("%s: shell built-in command\n", args[1]);
            return 0;
        }
    }
    //checking external commands
    char* cmd_path = find_cmd_in_path(args[1], env);
}

int cmd_echo(char** args, char** env) {
    bool new_line = true; //default echo wnds with\n, but, not if -n passed as a flag
    size_t i = 1;  //index of arg to read (used only to skip -n flag if inserted)
    if(args[1] != NULL && my_strcmp(args[1], "-n") == 0) {new_line = false;  i++;}

    for(; args[i]; i++) {
        if(args[i][0] == '$') {
            char* env_value = my_getenv(args[i] + 1, env);
            if(env_value) {printf("%s", env_value);}
            else {printf(" ");} //dont know why printf("") is needed, but, code doesnt work without it! :)
        }
        else {printf("%s", args[i]);}

        if(args[i+1] != NULL) {printf(" ");}
    }
    if(new_line) {printf("\n");}
    return 0;
}
