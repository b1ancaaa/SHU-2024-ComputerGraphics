#ifndef BRUSH_H
#define BRUSH_H

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <vector>

// #include "point.h"
using std::vector;

class Brush {
 private:
  vector<vector<int>> const *brush;
  QColor color;

 protected:
  // 1x1 brush
  vector<vector<int>> brush_1 = {{1}};

  // 3x3 brush
  vector<vector<int>> brush_3 = vector<vector<int>>(3, vector<int>(3, 1));
  // 5x5 brush
  vector<vector<int>> brush_5 = {{1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1}};
  // 7x7 brush
  vector<vector<int>> brush_7 = {{1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 1, 1, 1}};
  vector<vector<int>> brush_9 = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}};

  // 3x3 brush_circle
  vector<vector<int>> brush_3_C = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};
  // 5x5 brush_circle
  vector<vector<int>> brush_5_C = {{0, 0, 1, 0, 0},
                                   {0, 1, 1, 1, 0},
                                   {1, 1, 1, 1, 1},
                                   {0, 1, 1, 1, 0},
                                   {0, 0, 1, 0, 0}};
  // 7x7 brush_circle
  vector<vector<int>> brush_7_C = {{0, 0, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 0},
                                   {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
                                   {1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1, 0},
                                   {0, 0, 1, 1, 1, 0, 0}};
  // 9x9 brush_circle
  vector<vector<int>> brush_9_C = {
      {0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {0, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0}};

 public:
  QImage image;
  Brush() : brush(&brush_1) {}
  void setBrush(vector<vector<int>> const *brush) { this->brush = brush; }
  void setColor(QColor color) { this->color = color; }

  // switch brush
  void setBrush(int type) {
    switch (type) {
      case 1:
        this->brush = &brush_1;
        break;
      case 3:
        this->brush = &brush_3;
        break;
      case 5:
        this->brush = &brush_5;
        break;
      case 7:
        this->brush = &brush_7;
        break;
      case 9:
        this->brush = &brush_9;
        break;
      case -3:
        this->brush = &brush_3_C;
        break;
      case -5:
        this->brush = &brush_5_C;
        break;
      case -7:
        this->brush = &brush_7_C;
        break;
      case -9:
        this->brush = &brush_9_C;
        break;
      default:
        this->brush = &brush_1;
        break;
    }
  }
  void drawPixel(int x, int y, QColor c,QImage &image) {
    int width = brush->size();
    int x0 = x - (width - 1) / 2, y0 = y - (width - 1) / 2;
    for (int i = 0; i < width; i++) {
      for (int j = 0; j < width; j++) {
        if ((*brush)[i][j] == 1) {
          int xi = x0 + i;
          int yj = y0 + j;
          if (xi >= 0 && xi < image.width() && yj >= 0 && yj < image.height()) {
            image.setPixel(xi, yj, c.rgb());
          }
        }
      }
    }
  }
};
#endif  // BRUSH_H