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
    (void)init_dir;
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
    const char* builtin_cmds[] = {"pwd", "cd", "env", "setenv", "unsetenv", "which", "echo", "exit", NULL};
    for(size_t i = 0; builtin_cmds[i]; i++) {
        if(my_strcmp(builtin_cmds[i], args[1]) == 0) {
            printf("%s: shell built-in command\n", args[1]);
            return 0;
        }
    }
    //checking external commands
    char* full_path = find_cmd_in_path(args[1], env);
    if(full_path != NULL) {
        printf("%s\n", full_path);
        free(full_path);
        return 0;
    }
    else {
        printf("which - %s command not found in env", args[1]);
        return 1;
    }
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

char** cmd_setenv(char** args, char** env) {
    if(args[1] == NULL) {
        printf("usage cmd - setenv VAR=value\nor          setenv <variable> <value>\n"); //written so due to formatting in terminal
        return env;
    }

    int env_cnt = count_env_vars(env);
    char** new_env = malloc((env_cnt + 2) * sizeof(char*));
    if(!new_env) {
        perror("malloc failed in setenv");
        return env;
    }

    for(int i = 0; i < env_cnt; i++) {
        new_env[i] = my_strdup(env[i]);
        if(!new_env[i]) {
            perror("strdup failed in setenv - new_env");
            for(int j = 0; j < i; j++) {
                free(new_env[j]);
            }
            free(new_env);
            return env;
        }
    }

    char* new_var = NULL;
    if(args[2] == NULL) {  // Format is of the form VAR=value
        new_var = my_strdup(args[1]);
    }
    else {
        new_var = malloc(my_strlen(args[1]) + my_strlen(args[2]) + 2);
        if(new_var) {
            sprintf(new_var, "%s=%s", args[1], args[2]);
        }
    }

    if(!new_var) {
        perror("malloc failed in setenv - new_var");
        for (int i = 0; i < env_cnt; i++) {
            free(new_env[i]);
        }
        free(new_env);
        return env;
    }

    new_env[env_cnt] = new_var;
    new_env[env_cnt + 1] = NULL;

    return new_env;
}

char** cmd_unsetenv(char** args, char** env){
    if (!args[1]) {
        printf("usage cmd - unsetenv <variable>\n");
        return env;
    }

    int env_cnt = count_env_vars(env);
    char** new_env = malloc(env_cnt * sizeof(char*));
    if(!new_env) {
        perror("malloc failed in unsetenv");
        return env;
    }

    int j = 0;
    bool found = false;
    for (int i = 0; i < env_cnt; i++) {
        if(my_strncmp(env[i], args[1], my_strlen(args[1])) == 0 && env[i][my_strlen(args[1])] == '=') {
            found = true;
            free(env[i]);
        }
        else {
            new_env[j++] = env[i];
        }
    }

    if(!found) {
        printf("Variable %s not found in environment\n", args[1]);
        free(new_env);
        return env;
    }

    new_env[j] = NULL;
    return new_env;
}
