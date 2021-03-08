// const fs = require("fs");
// const { createCanvas } = require('canvas');
// const GIFEncoder = require('gifencoder');
const debug = false;

// const encoder = new GIFEncoder(width, height);
// // stream the results as they are available into myanimated.gif
// encoder.createReadStream().pipe(fs.createWriteStream('animated.gif'));
 
// encoder.start();
// encoder.setRepeat(0);   // 0 for repeat, -1 for no-repeat
// encoder.setDelay(200);  // frame delay in ms
// encoder.setQuality(10); 

const canvas = document.querySelector('#canvas');
const context = canvas.getContext('2d');

const width = canvas.width;
const height = canvas.height;

Number.prototype.clamp = function(min, max) {
  return Math.min(Math.max(this, min), max);
};

const cutoffLow = 0, cutoffHigh = 255; //256 * 15 / 16;

const modf = (value) => {
  return value.clamp(cutoffLow, cutoffHigh)
}

const rgb = (r, g, b, modf) => {
  r = modf(Math.floor(r) % 256);
  g = modf(Math.floor(g) % 256);
  b = modf(Math.floor(b) % 256);

  return `#${r.toString(16)}${g.toString(16)}${b.toString(16)}`;
}

let t = 0;

let offsetX = width / 2;
let offsetY = height / 2 + (debug ? height / 8 : 0);

let f = (x, y) => ((x - offsetX) ** 2 + (y - offsetY) ** 2);

let vf = [1, 1, 1];
let vx = [1, 1, 1];
let vy = [1, 1, 1];

let v = {
  "f": vf,
  "x": vx,
  "y": vy
}

setInterval(function() {
  context.fillStyle = `#000000`;
  context.fillRect(0, 0, width, height);  

  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      context.fillStyle = rgb(
        f(x + t * vx[0], y + t * vy[0]) * vf[0],
        f(x + t * vx[1], y + t * vy[1]) * vf[1],
        f(x + t * vx[2], y + t * vy[2]) * vf[2],
        modf
      );
      context.fillRect(x, y, 1, 1);
    }
  }

  if (debug) {
    context.fillStyle = "#000000";
    context.fillRect(0,0, 256, 64);
    context.fillStyle = "#ffffff";
    context.fillText(`l:${cutoffLow} h:${cutoffHigh} s:${startValue}t:${t}`, 12, 24);
  }

  t = (t + 1) % 256;
}, 100);

document.querySelectorAll('[data-vector]').forEach(element => element.addEventListener('change', function (event) {
  console.log(event);
  v[event.target.dataset.vector][event.target.dataset.index] = event.target.valueAsNumber;
}));