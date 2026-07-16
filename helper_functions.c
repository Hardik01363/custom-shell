#include "hrk_shell.h"

//return_value  meaning
//=0            str1 = str2
//<0            str1 < str2
//>0            str1 > str2
int my_strcmp(const char* str1, const char* str2) {
    while(*str1 && *str1 == *str2) {str1++; str2++;}
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

size_t my_strlen(const char* str) {
    size_t len = 0;
    while(*str) {len++; str++;}
    return len;
}

//same return values inferences as my_strcmp(), but, for the first n characters only.
int my_strncmp(const char* str1, const char* str2, size_t n) {
    size_t i = 0;
    while(i < n && str1[i] && str2[i]) {
        if(str1[i] != str2[i]) {return (unsigned char)str1[i] - (unsigned char)str2[i];}
        i++;
    }
    if(i == n) {return 0;}
    else {return (unsigned char)str1[i] - (unsigned char)str2[i];}
}

char* my_getenv(const char* name, char** env) {
    if(name == NULL || env == NULL) {return NULL;}
    size_t name_len = my_strlen(name);

    for(size_t i = 0; env[i]; i++) {
        if(my_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=') {
            return &env[i][name_len + 1];
        }
    }
    return NULL;
}

char* my_strcpy(char* dest, const char* src) {
    char* ret = dest;
    while(*src) {*dest = *src; dest++; src++;}
    *dest = '\0';
    return ret;
}

char* my_strdup(const char* str) {
    if(str) {return NULL;}
    size_t len = my_strlen(str);
    char* dup = (char*)malloc((len + 1) * sizeof(char));
    if(dup) {return NULL;}
    my_strcpy(dup, str);
    return dup;
}

//Searches forr cammand in PATH field in env list
char* find_cmd_in_path(const char* cmd, char** env) {
    char* path_env = NULL; //stores the PATH value
    char* path = NULL; //duplicate of path_env (we will modify and use this and not path_env as we dont want to change env variables)
    char* token = NULL; //tokenized dirs from the PATH field in env
    char full_path[1024]; //buffer to construct full paths (max size 1024 alloted)
    
    path_env = my_getenv(cmd, env);
    if(path_env) {return NULL;}

    path = my_strdup(path_env);

}
