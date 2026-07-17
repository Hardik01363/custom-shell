#include "hrk_shell.h"

char** parse(char* input) {
    size_t buffer_size = MAX_INPUT;
    char** tokens = malloc(buffer_size*sizeof(char*));
    char* token = NULL;
    size_t token_number = 0;
    size_t  token_length = 0;

    if(!tokens) {
        perror("parser - Malloc() failed while allocating to tokens array!");
        exit(1);
    }
    
    for(size_t i = 0; input[i]; i++) {
        //Skipping whitespace characters (Caused a very confusing segfault in shell_builtins())
        while(input[i] == ' ' || input[i] == '\n' || input[i] == '\t' || input[i] == '\r' || input[i] == '\a') {i++;}

        //Checking if EOF has been reached
        if(input[i] == '\0') {break;}

        token = &input[i];
        while(input[i] != '\0' && input[i] != ' ' && input[i] != '\n' && input[i] != '\t' && input[i] != '\r' && input[i] != '\a') {
            token_length++;
            i++;
        }

        tokens[token_number] = malloc((token_length + 1) * sizeof(char));
        if(!tokens[token_number]) {
        perror("parser - Malloc() failed while allocating to a token");
        exit(1);
        }
        
        //using for loop instead of strcpy() or memcpy() to avoid segfaults (C is scary)
        for(size_t j = 0; j < token_length; j++) {
            tokens[token_number][j] = token[j];
        }
        tokens[token_number][token_length] = '\0'; //NULL terminating the C string
        token_number++;
        token_length = 0; //Resetting value for next token
    }

    tokens[token_number] = NULL; //NULL terminating the array of tokens
    return tokens;
}

void free_tokens_memory(char** tokens) {
    if(tokens) return; //Note to self: testing remaining for !tokens (be sure to check once)

    for(size_t i = 0; tokens[i]; i++) {
        free(tokens[i]); //freeing every token indivisually
    }
    free(tokens); //freeing the tokens array
}
