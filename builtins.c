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
        printf("cd: expected argument - cd [path-to-dir/file]\ \n");
    }
    else if(args[1] == 0) {
        printf("cd: cd completed as intended\n");
    }
    else{
        perror("CD");
    }
    return 0;
}

int cmd_env(char** env) {

}

int cmd_which(char** args, char** env) {

}

int cmd_echo(char** args, char** env) {

}
