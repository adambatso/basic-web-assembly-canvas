#include <stdio.h>
#include <string.h>

int main() {
    printf("WASM Ready\n");
    return 1;
}

int getNum(int number) {
    return number * 2;
}

char * greet(char * name) {
    char * greeting = "hello ";
    strcat(greeting, name);

    return greeting;
}