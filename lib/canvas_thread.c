#include <emscripten.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <pthread.h>
#define NUM_OF_CIRCLES 8000
#define N 5 //number of thread

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

struct ArgsThread 
{
    int canvasWidth;
    int canvasHeight;
    int index;
    int endIndex;
    // struct Circle * circles;
    // struct AnimationCircle * animationCircles;
};


struct Circle circles[NUM_OF_CIRCLES];
struct AnimationCircle animationCircles[NUM_OF_CIRCLES];


void * changeCircles(struct ArgsThread * args) {
    // printf("name: %d\n", NUM_OF_CIRCLES);
    int canvasWidth = args->canvasWidth;
    int canvasHeight = args->canvasHeight;
    for (int i = args->index; i < args->endIndex; i++) {
        //right collistion
        if ((animationCircles[i].x + animationCircles[i].r) >= canvasWidth) {
            animationCircles[i].dx = 0;
        }

        //left collistion
        else if ((animationCircles[i].x - animationCircles[i].r) <= 0) {
            animationCircles[i].dx = 1;
        }

        // down collision
        if ((animationCircles[i].y + animationCircles[i].r) >= canvasHeight) {
            animationCircles[i].dy = 0;
        }
        // up collision
        else if ((animationCircles[i].y - animationCircles[i].r) <= 0) {
            animationCircles[i].dy = 1;
        }

        if (animationCircles[i].dx == 1) {
                animationCircles[i].x += animationCircles[i].vx;
        }
        else if (animationCircles[i].dx == 0) {
                animationCircles[i].x -= animationCircles[i].vx;
        }

        if (animationCircles[i].dy == 1) {
                animationCircles[i].y += animationCircles[i].vy;
        }
        else if (animationCircles[i].dy == 0) {
                animationCircles[i].y -= animationCircles[i].vy;
        }

        //update circles 
        circles[i].x = animationCircles[i].x;
        circles[i].y = animationCircles[i].y;
    }
    
}

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
    pthread_t   bg_thread;
    struct ArgsThread args;
    args.canvasHeight = canvasHeight;
    args.canvasWidth = canvasWidth;
    args.index = 2000;
    args.endIndex= 4000;
    if (pthread_create(&bg_thread, NULL, changeCircles, &args)) {
        perror("Thread create failed");
        return 1;
    }

    pthread_t   bg_thread2;
    struct ArgsThread args2;
    args2.canvasHeight = canvasHeight;
    args2.canvasWidth = canvasWidth;
    args2.index = 4000;
    args2.endIndex= 6000;
    if (pthread_create(&bg_thread2, NULL, changeCircles, &args2)) {
        perror("Thread create failed 2");
        return 1;
    }

    pthread_t   bg_thread3;
    struct ArgsThread args3;
    args3.canvasHeight = canvasHeight;
    args3.canvasWidth = canvasWidth;
    args3.index = 6000;
    args3.endIndex= 8000;
    if (pthread_create(&bg_thread3, NULL, changeCircles, &args3)) {
        perror("Thread create failed 3");
        return 1;
    }



//TODO:: craete thread dynamiclly
//     pthread_t t[N];
//     float arrayId[N];

    

// int amountOfCirclePerThread = NUM_OF_CIRCLES / N;
// for (int index = 0; index < N; index++) {
    
//     struct ArgsThread args4;
//     args4.canvasHeight = canvasHeight;
//     args4.canvasWidth = canvasWidth;
//     args4.index = amountOfCirclePerThread * index ;
//     args4.endIndex= amountOfCirclePerThread * (index +1);
    
//     pthread_create(&t[index], NULL, changeCircles, &args4);
//     // printf("creato il thread id=%lu\n", t[i]);
//     // arrayId[i] = t[i];
//     // printf("a[%d]=%f\n", i, arrayId[i]);
// }

// for (int index = 0; index < N; index++) {
//     if (pthread_join(t[index], NULL)) {
//         perror("Thread join failed 2");
//         return 2;
//     }
// }
//TODO:: end of 

    for (int i = 0; i < 2000; i++) {
        //right collistion
        if ((animationCircles[i].x + animationCircles[i].r) >= canvasWidth) {
            animationCircles[i].dx = 0;
        }

        //left collistion
        else if ((animationCircles[i].x - animationCircles[i].r) <= 0) {
            animationCircles[i].dx = 1;
        }

        // down collision
        if ((animationCircles[i].y + animationCircles[i].r) >= canvasHeight) {
            animationCircles[i].dy = 0;
        }
        // up collision
        else if ((animationCircles[i].y - animationCircles[i].r) <= 0) {
            animationCircles[i].dy = 1;
        }

        if (animationCircles[i].dx == 1) {
                animationCircles[i].x += animationCircles[i].vx;
        }
        else if (animationCircles[i].dx == 0) {
                animationCircles[i].x -= animationCircles[i].vx;
        }

        if (animationCircles[i].dy == 1) {
                animationCircles[i].y += animationCircles[i].vy;
        }
        else if (animationCircles[i].dy == 0) {
                animationCircles[i].y -= animationCircles[i].vy;
        }

        //update circles 
        circles[i].x = animationCircles[i].x;
        circles[i].y = animationCircles[i].y;
    }
    if (pthread_join(bg_thread, NULL)) {
        perror("Thread join failed");
        return 2;
    }
    if (pthread_join(bg_thread2, NULL)) {
        perror("Thread join failed 2");
        return 2;
    }
    if (pthread_join(bg_thread3, NULL)) {
        perror("Thread join failed 3");
        return 2;
    }
   
    return circles;
}



EM_JS( void, jsFunction, ( int x,int y,int r,int cr,int cg,int cb), {
        // context.beginPath();
        context.moveTo(x, y);
        context.arc(x, y, r, 2*Math.PI, false);
        context.fillStyle = `rgba(${cr},${cg},${cb}, 0.7)`;
        // context.fill();
        
});

EM_JS( void, clearBoard, ( int width,int height), {
       context.clearRect(0,0, width, height);
});

EM_JS( void, beginPath, (), {
       context.beginPath();
});
EM_JS( void, fillDrew, (), {
       context.fill();
});


// struct ArgsThreadPrint 
// {
//     int canvasWidth;
//     int canvasHeight;
//     int index;
//     int endIndex;
//     struct Circle * circlesPrint;
//     void * context;
//     // struct Circle * circles;
//     // struct AnimationCircle * animationCircles;
// };

// void * printCircles(struct ArgsThreadPrint * args) {
//     // printf("name: %d\n", NUM_OF_CIRCLES);
//     int canvasWidth = args->canvasWidth;
//     int canvasHeight = args->canvasHeight;
//     struct Circle * circlesPrint = args->circlesPrint;
//     for (int i = args->index; i < args->endIndex; i++) {
//         jsFunction(circlesPrint[i].x,circlesPrint[i].y,circlesPrint[i].r,circlesPrint[i].cr,circlesPrint[i].cg,circlesPrint[i].cb, args->context);
//     }
    
// }
// void print(int canvasWidth, int canvasHeight, void * context) {
//     clearBoard(canvasWidth, canvasHeight);
//     struct Circle * circlesPrint = getCircles(canvasWidth, canvasHeight);
    

// pthread_t   bg_thread;
//     struct ArgsThreadPrint args;
//     args.canvasHeight = canvasHeight;
//     args.canvasWidth = canvasWidth;
//     args.index = 1000;
//     args.endIndex= 2000;
//     args.circlesPrint = circlesPrint;
//     args.context = context;
//     if (pthread_create(&bg_thread, NULL, printCircles, &args)) {
//         perror("Thread create failed");
//         return;
//     }

//     pthread_t   bg_thread2;
//     struct ArgsThreadPrint args2;
//     args2.canvasHeight = canvasHeight;
//     args2.canvasWidth = canvasWidth;
//     args2.index = 2000;
//     args2.endIndex= 3000;
//     args.circlesPrint = circlesPrint;
//     args.context = context;
//     if (pthread_create(&bg_thread2, NULL, printCircles, &args2)) {
//         perror("Thread create failed 2");
//         return;
//     }

//     pthread_t   bg_thread3;
//     struct ArgsThreadPrint args3;
//     args3.canvasHeight = canvasHeight;
//     args3.canvasWidth = canvasWidth;
//     args3.index = 3000;
//     args3.endIndex= 4000;
//     args.circlesPrint = circlesPrint;
//     args.context = context;
//     if (pthread_create(&bg_thread3, NULL, printCircles, &args3)) {
//         perror("Thread create failed 3");
//         return;
//     }

//     // beginPath();
//     for (int i = 0; i < 1000; i++) {

//         jsFunction(circlesPrint[i].x,circlesPrint[i].y,circlesPrint[i].r,circlesPrint[i].cr,circlesPrint[i].cg,circlesPrint[i].cb, context);
//     }
//     // fillDrew();

//     if (pthread_join(bg_thread, NULL)) {
//         perror("Thread join failed");
//         return ;
//     }
//     if (pthread_join(bg_thread2, NULL)) {
//         perror("Thread join failed 2");
//         return ;
//     }
//     if (pthread_join(bg_thread3, NULL)) {
//         perror("Thread join failed 3");
//         return ;
//     }

// }


void print(int canvasWidth, int canvasHeight) {
    clearBoard(canvasWidth, canvasHeight);
    struct Circle * circlesPrint = getCircles(canvasWidth, canvasHeight);
    
    beginPath();
    for (int i = 0; i < NUM_OF_CIRCLES; i++) {

        jsFunction(circlesPrint[i].x,circlesPrint[i].y,circlesPrint[i].r,circlesPrint[i].cr,circlesPrint[i].cg,circlesPrint[i].cb);
    }
    fillDrew();
}