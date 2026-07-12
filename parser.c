#include "hrk_shell.h"

char** parse(char* input) {
    size_t buffer_size = MAX_INPUT;
    char** tokens = malloc(buffer_size*sizeof(char*));
    char* token = NULL;
    size_t  token_length = 0;

    if(!tokens) {
        perror("parser - Malloc() failed!");
        exit(EXIT_FAILURE);
    }

}
