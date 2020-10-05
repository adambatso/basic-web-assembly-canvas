#include <emscripten.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_OF_CIRCLES 100

//this hold the data for the first paint
struct Circle
{
    int x;
    int y;
    int r;
    int cr; 
    int cg;
    int cb;
};
// this hold the data for the animation
struct AnimationCircle
{
    int x; // x coordinate
    int y; // y coordinate
    int r; //radius 
    int vx; //velocity x 
    int vy; // velocity y
    int dx; // direction x
    int dy; // directino y
};

struct Circle circles[NUM_OF_CIRCLES];
struct AnimationCircle animationCircles[NUM_OF_CIRCLES];

int getRand(int max) {
    return (rand() % max) +1;
}
int main() {
    printf("WASM Ready\n");

    srand(time(NULL));

    for( int i = 0; i < NUM_OF_CIRCLES; i++) {
        int rad = getRand(getRand(50));
        int x = getRand(getRand(2000)) + rad; //avoid coliistions
        int y = getRand(getRand(2000)) + rad;


        animationCircles[i].r = rad;
        animationCircles[i].x = x;
        animationCircles[i].y = y;
        animationCircles[i].vx = getRand(10);
        animationCircles[i].vy = getRand(10);
        animationCircles[i].dx = 1; //move forward
        animationCircles[i].dy = 1;


        circles[i].r = rad;
        circles[i].x = x;
        circles[i].y = y;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
        
    }

    // Call js function (eval)
    EM_ASM({render($0, $1)}, NUM_OF_CIRCLES * 6, 6);
    return 1;
}


struct Circle * getCircles(int canvasWidth, int canvasHeight) {

    for (int i = 0; i < NUM_OF_CIRCLES; i++) {
        //right collistion
        if ((animationCircles[i].x + animationCircles[i].r) >= canvasWidth) {
            animationCircles[i].dx = 0;
        }

        //left collistion
        if ((animationCircles[i].x - animationCircles[i].r) <= 0) {
            animationCircles[i].dx = 1;
        }

        // down collision
        if ((animationCircles[i].y + animationCircles[i].r) >= canvasHeight) {
            animationCircles[i].dy = 0;
        }
        // up collision
        if ((animationCircles[i].y - animationCircles[i].r) <= 0) {
            animationCircles[i].dy = 1;
        }

        if (animationCircles[i].dx == 1) {
                animationCircles[i].x += animationCircles[i].vx;
        }
        else {
                animationCircles[i].x -= animationCircles[i].vx;
        }

        if (animationCircles[i].dy == 1) {
                animationCircles[i].y += animationCircles[i].vy;
        }
        else {
                animationCircles[i].y -= animationCircles[i].vy;
        }

        //update circles 
        circles[i].x = animationCircles[i].x;
        circles[i].y = animationCircles[i].y;
    }
    
    return circles;
}