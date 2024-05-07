var cvs = document.getElementById("canvas");
cvs.height = window.innerHeight;//-window.innerHeight%240;
cvs.width = window.innerWidth;//-window.innerWidth%256;
var ctx = cvs.getContext("2d");
ctx.imageSmoothingEnabled = false;
var k = {x: window.innerHeight/240, y: window.innerWidth/256}

var centX = cvs.width/2;
var centY = cvs.height/2;
var xPos = cvs.width/4;
var yPos = cvs.height/4;
var aimxy = {x: centX, y: centY, tap: false, hold: false};
var shot = {a: 100, shot: false};
var duckxy = {x: centX/2, y: centY};

var bird = new Image();
var bg = new Image();
var aim = new Image();

bird.src = "/img/ducks.png";
bg.src = "/img/scenes.png";
aim.src = "/img/aim.png";

function circ (x = cvs.width/2, y = cvs.height/2, radius) {
    ctx.beginPath()
    ctx.arc(x, y, radius, 0, 2*Math.PI, false);
    ctx.fillStyle = 'yellow';
    ctx.fill();
    ctx.lineWidth = 5;
    ctx.strokeStyle = 'red';
    ctx.stroke();
}

function drawCanv() {
    ctx.drawImage(bg, 0, 0, 256, 240, 0, 0, cvs.width, cvs.height);
}

function flyDuck(duckxy) {
    ctx.drawImage(bird, 0, 0, 39, 40, duckxy.x, duckxy.y, 39*k.x, 40*k.x);
}

function draw(aimxy) {
    // Какой-либо код
    duckxy.x = 100;
    duckxy.y = 300;
    flyDuck(duckxy);
    //duckxy.x += 10;
    //duckxy.y += 30;

    ctx.drawImage(aim, aimxy.x, aimxy.y);


    //requestAnimationFrame(draw); // Вызов функции постоянно
}

// При нажатии на какую-либо кнопку
document.addEventListener("keydown", keyDown);
// Вызывается метод someMethod
function keyDown() {
 // Изменяем что-то в коде
}

function run() {
    const xhr = new XMLHttpRequest();
    xhr.open('GET', 'get_data');
    xhr.onload = function()
    {
    if (xhr.status === 200)
    {
        const response = xhr.responseText;
        console.log(response); // x [0, 1919], y [0, 1080]
        aimxy = JSON.parse(response);
    }
    else 
    {
        console.log('Ошибка загрузки данных: ' + xhr.status);
    }
    };
    xhr.send();
    drawCanv();
    draw(aimxy); // Вызов функции из-вне function draw()
};
drawCanv();
setInterval(run, 16);