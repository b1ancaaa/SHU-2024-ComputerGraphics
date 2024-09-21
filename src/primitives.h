#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <QWidget>

#include "brush.h"

class Primitives : public QWidget, public Brush {
  Q_OBJECT
 public:
  explicit Primitives(QWidget *parent = nullptr);
  void drawLine(int x1, int y1, int x2, int y2, QColor color);
  void drawRect(int x1, int y1, int x2, int y2, QColor color);
  void drawCirclePoints(int x, int x0, int y, int y0, QColor color);
  void drawCircle(int x, int y, int radius, QColor color);
  void drawEllipse(int x, int y, int a, int b, QColor color);
  void drawPolygon();

 protected:
  void paintEvent(QPaintEvent *) override;

 private:
  QImage image;
};

#endif  // CANVAS_H