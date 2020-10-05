context = null;
canvasHeight = null;
canvasWidth = null;
onmessage = function(e) {
    
    
    
    if (!context) {
        let canvas = e.data.canvas;
        canvasHeight = canvas.height;
        canvasWidth = canvas.width;
        console.log('%c var name', 'font-size:20px;color:lime;', canvasHeight);
        console.log('%c canvasWidth', 'font-size:20px;color:lime;', canvasWidth);
        context = canvas.getContext('2d');
    }
    else {
    const circles = e.data.circles;
    const circleStructureSize = e.data.circleStructureSize;
    const indexStart = e.data.indexStart;
    const indexEnd = e.data.indexEnd;
    
    context.clearRect(0,0, canvasWidth, canvasHeight)
    for (let i =indexStart; i < indexEnd; i += circleStructureSize) {
        let circle = circles.slice(i, i + circleStructureSize);
        context.beginPath();
        
        context.moveTo(circle[0], circle[1]);
        context.arc(circle[0], circle[1], circle[2], 2*Math.PI, false);
        context.fillStyle = `rgba(${circle[3]},${circle[4]},${circle[5]}, 0.7)`;
        context.fill();    
    }
      
    }
   

  }