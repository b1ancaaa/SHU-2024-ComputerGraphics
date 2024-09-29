#ifndef PEN_H
#define PEN_H

#include <qcontainerfwd.h>

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QVector>
class Pen {
 public:
  Pen();
  Pen(QColor color, int brush_type);
  void setBrushColor(QColor color);
  void setBrushSize(int size);
  void drawPixel(QVector<QPoint> points, QImage &image);

 private:
  QColor brush_color;
  QVector<QVector<int>> brush_size;
  // 生成笔刷
  QVector<QVector<int>> generateCircularBrush(int size);
  QVector<QVector<int>> generateSquareBrush(int size);
};

#endif  // PEN_H