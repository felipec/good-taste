const pr = window.devicePixelRatio;
const space = (40 / pr) | 0;
const node_size = { w: (80 / pr) | 0, h: (40 / pr) | 0 };
const node_box = { w: node_size.w + space, h: node_size.h };
const font_size = (20 / pr) | 0;

const blue = 'hsl(240, 75%, 75%)';
const red = 'hsl(0, 75%, 75%)';
const green = 'hsl(120, 75%, 75%)';

function draw_arrow(x0, y0, x1, y1) {
  const head_size = (5 / pr) | 0;
  const head_angle = Math.PI / 6;
  const width = (4 / pr) | 0;

  const angle = Math.atan2(y1 - y0, x1 - x0);

  ctx.lineWidth = width;
  ctx.lineCap = 'square';
  ctx.lineJoin = 'miter';

  const wx = width * Math.cos(angle);
  const wy = width * Math.sin(angle);
  const tox = x1 - wx;
  const toy = y1 - wy;

  ctx.beginPath();
  ctx.moveTo(x0, y0);
  ctx.lineTo(tox - wx, toy - wy);
  ctx.stroke();

  ctx.beginPath();
  ctx.moveTo(tox, toy);
  ctx.lineTo(tox - head_size * Math.cos(angle - head_angle), toy - head_size * Math.sin(angle - head_angle));
  ctx.lineTo(tox - head_size * Math.cos(angle + head_angle), toy - head_size * Math.sin(angle + head_angle));
  ctx.closePath();
  ctx.stroke();
  ctx.fill();
}

function fill_rect(color, x, y, w, h) {
  ctx.save();
  ctx.fillStyle = color;
  ctx.fillRect(x, y, w, h);
  ctx.restore();
}

function draw_text(text, x, y, w, h) {
  ctx.font = `${font_size}px monospace`;
  ctx.textAlign = 'center';
  ctx.textBaseline = 'middle';
  ctx.fillText(text, x + w / 2, y + (font_size / 16) + h / 2);
}

function draw_node(x, y, value) {
  const [w, h] = [node_size.w, node_size.h];

  fill_rect(blue, x + w / 2, y, w / 2, h);

  ctx.strokeRect(x, y, w, h);

  ctx.beginPath();
  ctx.moveTo(x + w / 2, y);
  ctx.lineTo(x + w / 2, y + h);
  ctx.stroke();

  draw_text(value, x, y, w / 2, h);

  draw_arrow(x + w * 3 / 4, y + h / 2, x + w + space - 2, y + h / 2);

  ctx.beginPath();
  ctx.arc(x + w * 3 / 4, y + h / 2, h / 6, 0, 2 * Math.PI);
  ctx.fill();
}

function draw_head(x, y) {
  const [w, h] = [node_size.w, node_size.h];

  fill_rect(blue, x, y, w, h);
  ctx.strokeRect(x, y, w, h);
  draw_text('head', x, y, w, h);
  draw_arrow(x + w, y + h / 2, x + w + space - 2, y + h / 2);
}

function draw_null(x, y) {
  const [w, h] = [node_size.w, node_size.h];

  fill_rect(red, x, y, w, h);
  draw_text('NULL', x, y, w, h);
}

function draw_pointer(name, color, x, y, w) {
  const h = node_size.h;

  fill_rect(color, x, y, w, h);
  ctx.strokeRect(x, y, w, h);
  draw_text(name, x, y, w, h);

  draw_arrow(x + w / 2, y, x + w / 2, y - space);
}

function init(width, height) {
  ctx.canvas.width = width;
  ctx.canvas.height = height;

  ctx.lineWidth = (4 / pr) | 0;
  ctx.lineJoin = 'round';
}

function draw() {
  ctx = document.getElementById('node')?.getContext('2d');

  if (ctx) {
    init(4 + node_box.w, 4 + node_box.h);
    draw_node(2, 2, '0');
  }

  ctx = document.getElementById('list')?.getContext('2d');

  if (ctx) {
    init(4 + 4 * node_box.w + node_size.w, 4 + node_box.h);

    draw_head(2, 2);
    draw_node(2 + 1 * node_box.w, 2, '0');
    draw_node(2 + 2 * node_box.w, 2, '1');
    draw_node(2 + 3 * node_box.w, 2, '2');
    draw_null(2 + 4 * node_box.w, 2);
  }

  ctx = document.getElementById('traditional')?.getContext('2d');

  if (ctx) {
    init(4 + 4 * node_box.w + node_size.w, 4 + 2 * node_box.h + space);

    draw_head(2, 2);
    draw_node(2 + 1 * node_box.w, 2, '0');
    draw_node(2 + 2 * node_box.w, 2, '1');
    draw_node(2 + 3 * node_box.w, 2, '2');
    draw_null(2 + 4 * node_box.w, 2);

    draw_pointer('prev', blue, 2 + 1 * node_box.w, 2 + node_size.h + space, node_size.w);
    draw_pointer('walk', blue, 2 + 2 * node_box.w, 2 + node_size.h + space, node_size.w);
  }

  ctx = document.getElementById('improved')?.getContext('2d');

  if (ctx) {
    init(4 + 4 * node_box.w + node_size.w, 4 + 2 * node_box.h + space);

    draw_head(2, 2);
    draw_node(2 + 1 * node_box.w, 2, '0');
    draw_node(2 + 2 * node_box.w, 2, '1');
    draw_node(2 + 3 * node_box.w, 2, '2');
    draw_null(2 + 4 * node_box.w, 2);

    draw_pointer('p', green, 2 + node_box.w + node_size.w / 2, 2 + node_size.h + space, node_size.w / 2);
  }

  ctx = document.getElementById('linux')?.getContext('2d');

  if (ctx) {
    init(4 + 4 * node_box.w + node_size.w, 4 + 2 * node_box.h + space);

    draw_node(2 + 0 * node_box.w, 2, 'h');
    draw_node(2 + 1 * node_box.w, 2, '0');
    draw_node(2 + 2 * node_box.w, 2, '1');
    draw_node(2 + 3 * node_box.w, 2, '2');
    draw_null(2 + 4 * node_box.w, 2);

    draw_pointer('p', blue, 2 + node_size.w / 2, 2 + node_size.h + space, node_size.w / 2);
  }
}

draw();
