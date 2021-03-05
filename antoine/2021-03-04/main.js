const fs = require("fs");
const { createCanvas } = require('canvas');
const GIFEncoder = require('gifencoder');

const width = height = 256;
const debug = false;

const encoder = new GIFEncoder(width, height);
// stream the results as they are available into myanimated.gif
encoder.createReadStream().pipe(fs.createWriteStream('animated.gif'));
 
encoder.start();
encoder.setRepeat(0);   // 0 for repeat, -1 for no-repeat
encoder.setDelay(200);  // frame delay in ms
encoder.setQuality(10); 

const canvas = createCanvas(width, height);
const context = canvas.getContext('2d');

Number.prototype.clamp = function(min, max) {
  return Math.min(Math.max(this, min), max);
};

let startValue = 255;
let domain = 49;
let tail = 587;
let power = -9;
let multiplier = 1 + 10**power * tail;

let value = startValue;

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

for (let i = 1; i <= 240; i ++) {
  context.fillStyle = `#000000`;
  context.fillRect(0, 0, width, height);
  let quotient = 1 / (value + domain);
  let offsetX = 0;
  let offsetY = 0 + (debug ? 32 : 0);

  value *= multiplier;

  let f = (x, y) => (((x - offsetX) * (x - offsetX) + (y - offsetY) * (y - offsetY)) / quotient);
  
  let vf = [0.01, 0, 0];//[0., 0., 1.723913];//[1.33, 0.89, 27 / 37];
  let vx = [1253/256, -254/256, 255/256];//[0.33, 0.66, 1];
  let vy = [-255/256, 254/256, 1253/256];//[1.33, 0.97, 32 / 37];

  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      context.fillStyle = rgb(
        f(x * vx[0], y * vy[0]) * vf[0],
        f(x * vx[1], y * vy[1]) * vf[1],
        f(x * vx[2], y * vy[2]) * vf[2],
        modf
      );
      context.fillRect(x, y, 1, 1);
    }
  }

  if (debug) {
    context.fillStyle = "#000000";
    context.fillRect(0,0, 256, 64);
    context.fillStyle = "#ffffff";
    context.fillText(`c:${cutoff} s:${startValue} d:${domain} p:${power} t:${tail} f:${i}`, 12, 24);
    context.fillText(`q:${quotient}`, 12, 48);
  }

  encoder.addFrame(context);
}

encoder.finish();

// const buffer = canvas.toBuffer('image/png', {compressionLevel: 8});
// fs.writeFileSync('out.png', buffer);