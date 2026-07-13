#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#define MAX_INPUT 1024

char** parse(char* input);
void free_tokens_memory(char** tokens);
int shell_builtins(char** args, char** env, char* init_dir);
int my_strcmp(const char* str1, const char* str2);

int cmd_pwd();
int cmd_cd(char** args, char* init_dir);
int cmd_env(char** env);
int cmd_which(char** args, char** env);
int cmd_echo(char** args, char** env);
char** cmd_setenv(char** args, char** env);
char** cmd_unsetenv(char** args, char** env);
