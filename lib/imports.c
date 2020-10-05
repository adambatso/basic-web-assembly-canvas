#include <emscripten.h>
#include <stdio.h>
#include <string.h>

EM_JS( void, jsFunction, (int n, int n2), {
    console.log(" in Em js ,", n , ' ', n2);
});

int main() {
    printf("WASM Ready\n");

    // Call js function (eval)
    emscripten_run_script("console.log('hello from C');");

    // call js function eval async 
    emscripten_async_run_script("console.log('hello from C 2 second');", 2000);

    int jsVal = emscripten_run_script_int("getNum()");

    printf("from get num %d\n", jsVal);

    jsFunction(44,55);
    return 1;
}


char * greet(char * name) {
    char * greeting = "hello ";
    strcat(greeting, name);

    return greeting;
}