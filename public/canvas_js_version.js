

const NUM_OF_CIRCLES = 100;



const circles = Array(NUM_OF_CIRCLES);
const animationCircles = Array(NUM_OF_CIRCLES);

function getRand(max) {
    return Math.floor((Math.random() * max));
}
function main() {

    for( let i = 0; i < NUM_OF_CIRCLES; i++) {
        const rad = getRand(getRand(50));
        const x = getRand(getRand(2000)) + rad; //avoid coliistions
        const y = getRand(getRand(2000)) + rad;

        animationCircles[i]={};
        animationCircles[i].r = rad;
        animationCircles[i].x = x;
        animationCircles[i].y = y;
        animationCircles[i].vx = getRand(10);
        animationCircles[i].vy = getRand(10);
        animationCircles[i].dx = 1; //move forward
        animationCircles[i].dy = 1;

        circles[i] ={};
        circles[i].r = rad;
        circles[i].x = x;
        circles[i].y = y;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
        
    }
console.log('%c In finishMain', 'font-size:20px;color:blue;');
    // Call js function (eval)
    render()
    
}

function getCircles(canvasWidth, canvasHeight) {

    for (let i = 0; i < NUM_OF_CIRCLES; i++) {
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

