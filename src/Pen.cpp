#include "Pen.h"

#include <qcontainerfwd.h>

Pen::Pen() {
  brush_color = Qt::black;
  brush_size = &brush_1;
}

Pen::Pen(QColor color, int brush_type) {
  brush_color = color;
  setBrushSize(brush_type);
}

void Pen::setBrushColor(QColor color) { brush_color = color; }

QColor Pen::brushColor() const { return brush_color; }

void Pen::drawPixel(QList<QPoint> points, QImage& image) {
  int brush_half_size = brush_size->size() / 2;
  for (auto pos : points) {
    for (int i = 0; i < brush_size->size(); i++) {
      for (int j = 0; j < brush_size->size(); j++) {
        if (brush_size->at(i).at(j) == 1) {
          int x = pos.x() + i - brush_half_size;
          int y = pos.y() + j - brush_half_size;
          if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
            image.setPixelColor(x, y, brush_color);
          }
        }
      }
    }
  }
}

void Pen::setBrushSize(int size) {
  switch (size) {
    case 1:
      brush_size = &brush_1;
      break;
    case 3:
      brush_size = &brush_3;
      break;
    case 5:
      brush_size = &brush_5;
      break;
    case 7:
      brush_size = &brush_7;
      break;
    case 9:
      brush_size = &brush_9;
      break;
    case -3:
      brush_size = &brush_r_3;
      break;
    case -5:
      brush_size = &brush_r_5;
      break;
    case -7:
      brush_size = &brush_r_7;
      break;
    case -9:
      brush_size = &brush_r_9;
      break;
    default:
      brush_size = &brush_1;
      break;
  }
}
