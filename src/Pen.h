#ifndef PEN_H
#define PEN_H
#include <qcolor.h>
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
  QColor brushColor() const;
  void drawPixel(QList<QPoint> points, QImage& image);
  const QVector<QVector<int>> brush_1 = {{1}};

  const QVector<QVector<int>> brush_r_3 = {{0, 1, 0}, {1, 1, 1}, {0, 1, 0}};

  const QVector<QVector<int>> brush_r_5 = {{0, 0, 1, 0, 0},
                                           {0, 1, 1, 1, 0},
                                           {1, 1, 1, 1, 1},
                                           {0, 1, 1, 1, 0},
                                           {0, 0, 1, 0, 0}};

  const QVector<QVector<int>> brush_r_7 = {
      {0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0}, {0, 1, 1, 1, 1, 1, 0},
      {1, 1, 1, 1, 1, 1, 1}, {0, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 1, 1, 0, 0},
      {0, 0, 0, 1, 0, 0, 0}};

  const QVector<QVector<int>> brush_r_9 = {
      {0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 0, 0},
      {0, 1, 1, 1, 1, 1, 1, 1, 0}, {0, 0, 1, 1, 1, 1, 1, 0, 0},
      {0, 0, 0, 1, 1, 1, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0}};

  const QVector<QVector<int>> brush_3 = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

  const QVector<QVector<int>> brush_5 = {{1, 1, 1, 1, 1},
                                         {1, 1, 1, 1, 1},
                                         {1, 1, 1, 1, 1},
                                         {1, 1, 1, 1, 1},
                                         {1, 1, 1, 1, 1}};

  const QVector<QVector<int>> brush_7 = {
      {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1}};

  const QVector<QVector<int>> brush_9 = {
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1}};

 private:
  QColor brush_color;
  QVector<QVector<int>> const* brush_size;
};

#endif  // PEN_H