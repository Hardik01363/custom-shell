#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT 1024

char** parse(char* input);
void free_tokens_memory(char** tokens);
int shell_builtins(char** args, char** env, char* init_dir);
int my_strcmp(const char* str1, const char* str2);
size_t my_strlen(const char* str);
int my_strncmp(const char* str1, const char* str2, size_t n);
char* my_getenv(const char* name, char** env);
char* my_strcpy(char* dest, const char* src);
char* my_strdup(const char* str);
char* my_strchr(const char* str, char c);
char* my_strtok(char* str, const char* pivot);
char* find_cmd_in_path(const char* cmd, char** env);
int count_env_vars(char** env);
char* my_strncpy(char* dest, const char* src, size_t n);

int cmd_pwd();
int cmd_cd(char** args, char* init_dir);
int cmd_env(char** env);
int cmd_which(char** args, char** env);
int cmd_echo(char** args, char** env);
char** cmd_setenv(char** args, char** env);
char** cmd_unsetenv(char** args, char** env);

int executor(char** args, char** env);
int child_process(char** args, char** env);
char* get_path(char** env);
char** split_paths(char* paths, int* count);

