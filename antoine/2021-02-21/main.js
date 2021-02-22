const fs = require("fs");
const { createCanvas } = require('canvas');

const width = height = 256;

const canvas = createCanvas(width, height);
const context = canvas.getContext('2d');

for (let y = 0; y < height; y++) {
  for (let x = 0; x < width; x++) {
    context.fillStyle = `black`;
    context.fillRect(x, y, 1, 1);
  }
}

for (let y = 0; y < height; y++) {
  for (let x = 0; x < width; x++) {
    context.fillStyle = `rgba(${y * y / x}, ${x * x / y}, ${y * y / x}, 1)`;
    context.fillRect(x, y, 1, 1);
  }
}

const buffer = canvas.toBuffer('image/png');
fs.writeFileSync('out.png', buffer);