#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_INPUT 1024

char** parse(char* input);
void free_tokens_memory(char** tokens);
int shell_builts(char** args, char** env, char* init_dir);
