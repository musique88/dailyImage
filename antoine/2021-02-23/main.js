const fs = require("fs");
const { createCanvas } = require('canvas');

const width = height = 256;

const canvas = createCanvas(width, height);
const context = canvas.getContext('2d');

for (let y = 0; y < height; y++) {
  for (let x = 0; x < width; x++) {
    context.fillStyle = `#000000`;
    context.fillRect(x, y, 1, 1);
  }
}

Number.prototype.clamp = function(min, max) {
  return Math.min(Math.max(this, min), max);
};

const quotient = 1 / (89);
const offsetX = 128;
const offsetY = 128;
const f = (x, y) => (((x - offsetX) * (x - offsetX) + (y - offsetY) * (y - offsetY)) / quotient) % 255;

const rgb = (r, g, b) => {
  r = Math.floor(r).clamp (0, 255);
  g = Math.floor(g).clamp(0, 255);
  b = Math.floor(b).clamp(0, 255);

  return `#${r.toString(16)}${g.toString(16)}${b.toString(16)}`;
}

for (let y = 0; y < height; y++) {
  for (let x = 0; x < width; x++) {
    context.fillStyle = rgb(f(x, y), f(x, y), f(x, y));
    context.fillRect(x, y, 1, 1);
  }
}

const buffer = canvas.toBuffer('image/png', {compressionLevel: 8});
fs.writeFileSync('out.png', buffer);