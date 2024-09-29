#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <QtAlgorithms>
#include <QtMath>

#include "Pen.h"

class Primitive
{
  public:
    enum Type
    {
        Line,
        Polygon,
        Circle,
        Ellipse,
        Curve
    };
    Primitive();
    Primitive(Pen pen, Type type, QVector<QPoint> args);
    QPoint center() const;
    Type type() const;
    Pen pen();
    QVector<QPoint> args() const;
    QVector<QPoint> points() const;
    void setArgs(QVector<QPoint> args);
    void setPoints(QVector<QPoint> points);
    void drawPrimitive(QImage &image);
    void setPen(QColor color = Qt::black, int brusjh_size = 1);
    static QVector<QPoint> drawLine(QVector<QPoint> args);    // 绘制直线
    static QVector<QPoint> drawRect(QVector<QPoint> args);    // 绘制矩形
    static QVector<QPoint> drawPolygon(QVector<QPoint> args); // 绘制多边形
    // static QVector<QPoint> drawCircle(QVector<QPoint> args);	// 绘制圆形
    static QVector<QPoint> drawEllipse(QVector<QPoint> args); // 绘制椭圆
    static QVector<QPoint> drawCurve(QVector<QPoint> args);   // 绘制曲线
    QVector<QPoint> translate(QPoint pos);                    // 平移
    QVector<QPoint> rotate(float r);                          // 旋转
    QVector<QPoint> scale(float s);                           // 缩放
    QVector<QPoint> clip(QPoint lt, QPoint rb);               // 裁剪

  private:
    Type _type;
    QPoint _center;
    QVector<QPoint> _args;
    QVector<QPoint> _points;
    Pen _pen;
};
#endif // PRIMITIVE_H
