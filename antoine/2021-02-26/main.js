const fs = require("fs");
const { createCanvas } = require('canvas');
const GIFEncoder = require('gifencoder');

const width = height = 256;

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

const modf = (value) => {
  return value;
  //return (value > 250) ? value : 0; 
}

const rgb = (r, g, b, modf) => {
  r = modf(Math.floor(r).clamp(0, 255));
  g = modf(Math.floor(g).clamp(0, 255));
  b = modf(Math.floor(b).clamp(0, 255));

  return `#${r.toString(16)}${g.toString(16)}${b.toString(16)}`;
}

let startValue = 0.000125;
let multiplier = 1.00000189;

for (let i = 1; i < 100; i ++) {
  context.fillStyle = `#000000`;
  context.fillRect(0, 0, width, height);
  
  let quotient = 1 / (startValue);
  let offsetX = 128;
  let offsetY = 128;

  startValue *= multiplier;

  let f = (x, y) => (((x - offsetX) * (x - offsetX) + (y - offsetY) * (y - offsetY)) / quotient) % 255;
  
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      context.fillStyle = rgb(f(quotient * i + x, y), f(x, quotient * i + y), f(quotient * i + x, quotient * i + y), modf);
      context.fillRect(x, y, 1, 1);
    }
  }

  encoder.addFrame(context);
}
for (let i = 99; i >= 1; i--) {
  context.fillStyle = `#000000`;
  context.fillRect(0, 0, width, height);
  
  let quotient = 1 / (startValue);
  let offsetX = 128;
  let offsetY = 128;

  startValue *= multiplier;

  let f = (x, y) => (((x - offsetX) * (x - offsetX) + (y - offsetY) * (y - offsetY)) / quotient) % 255;
  
  for (let y = 0; y < height; y++) {
    for (let x = 0; x < width; x++) {
      context.fillStyle = rgb(f(quotient * i + x, y), f(x, quotient * i + y), f(quotient * i + x, quotient * i + y), modf);
      context.fillRect(x, y, 1, 1);
    }
  }

  encoder.addFrame(context);
}

encoder.finish();

// const buffer = canvas.toBuffer('image/png', {compressionLevel: 8});
// fs.writeFileSync('out.png', buffer);