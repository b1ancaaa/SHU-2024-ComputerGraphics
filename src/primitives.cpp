#include "primitives.h"

#include <cmath>

Primitives::Primitives(QWidget *parent)
    : QWidget(parent), image(800, 600, QImage::Format_RGB32) {
  image.fill(Qt::white);
}
// draw line
void Primitives::drawLine(int x1, int y1, int x2, int y2, QColor color) {
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int sx = (x1 < x2) ? 1 : -1;
  int sy = (y1 < y2) ? 1 : -1;
  int err = dx - dy;

  while (true) {
    drawPixel(x1, y1, color, image);  // 在图像上绘制点

    if (x1 == x2 && y1 == y2) break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x1 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y1 += sy;
    }
  }
  update();  // 更新画布
}

// draw rectangle
void Primitives::drawRect(int x1, int y1, int x2, int y2, QColor color) {
  drawLine(x1, y1, x2, y1, color);
  drawLine(x1, y1, x1, y2, color);
  drawLine(x2, y1, x2, y2, color);
  drawLine(x1, y2, x2, y2, color);
  update();  // 更新画布
}

// draw circle
void Primitives::drawCirclePoints(int x, int x0, int y, int y0, QColor color) {
  drawPixel(x + x0, y + y0, color, image);
  drawPixel(x - x0, y + y0, color, image);
  drawPixel(x + x0, y - y0, color, image);
  drawPixel(x - x0, y - y0, color, image);
  drawPixel(x + y0, y + x0, color, image);
  drawPixel(x - y0, y + x0, color, image);
  drawPixel(x + y0, y - x0, color, image);
  drawPixel(x - y0, y - x0, color, image);
}
void Primitives::drawCircle(int x, int y, int radius, QColor color) {
  int x0 = 0, y0 = radius;
  int d = 3 - 2 * radius;
  drawCirclePoints(x, x0, y, y0, color);
  while (y0 >= x0) {
    x0++;
    if (d > 0) {
      y0--;
      d = d + 4 * (x0 - y0) + 10;
    } else {
      d = d + 4 * x0 + 6;
    }
    drawCirclePoints(x, x0, y, y0, color);
  }
  update();  // 更新画布
}

// draw ellipse
void Primitives::drawEllipse(int x, int y, int a, int b, QColor color) {
  int x0 = 0, y0 = b;
  float d1, d2;
  d1 = b * b + a * a * (-b + 0.25);  // d1置初值
  drawPixel(x + x0, y + y0, color, image);
  while (b * b * (x0 + 1) < a * a * (y0 - 0.5))  // 直到上下分界点
  {
    if (d1 < 0) {
      d1 += b * b * (2 * x0 + 3);
      x0++;
    }  // 取右点,d1增
    else {
      d1 += (b * b * (2 * x0 + 3) + a * a * (-2 * y0 + 2));
      x0++;
      y0--;
    }  // 取右下点，d1增
    drawPixel(x + x0, y + y0, color, image);
    drawPixel(x + x0, y - y0, color, image);
    drawPixel(x - x0, y + y0, color, image);
    drawPixel(x - x0, y - y0, color, image);
  }  // 上半部分结束

  // 下半部分开始
  d2 = sqrt(b * (x0 + 0.5)) + sqrt(a * (y0 - 1)) - sqrt(a * b);
  // d2置初值，sqr为平方函数
  while (y0 > 0)  // 直到x坐标轴
  {
    if (d2 < 0) {
      d2 += b * b * (2 * x0 + 2) + a * a * (-2 * y0 + 3);
      x0++;
      y0--;
    }  // 取右下点
    else {
      d2 += a * a * (-2 * y0 + 3);
      y0--;
    }  // 取下点
    drawPixel(x + x0, y + y0, color, image);
    drawPixel(x + x0, y - y0, color, image);
    drawPixel(x - x0, y + y0, color, image);
    drawPixel(x - x0, y - y0, color, image);
  }
    update();  // 更新画布
}

void Primitives::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.drawImage(0, 0, image);
}