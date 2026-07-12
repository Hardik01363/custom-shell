#include <stdio.h>

void shell_loop(char** env) {

}

int main(int argc, char** argv, char** env) {
    //we wont need argc and argv
    (void)argc;
    (void)argv;
    
    shell_loop(env);

    return 0;
}
