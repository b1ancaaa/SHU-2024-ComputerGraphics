#include "Primitive.h"

Primitive::Primitive()
{
}

Primitive::Primitive(Pen pen, Primitive::Type type, QVector<QPoint> args) : _type(type), _pen(pen)
{
    setArgs(args);
}

QPoint Primitive::center() const
{
    return _center;
}

Primitive::Type Primitive::type() const
{
    return _type;
}

Pen Primitive::pen()
{
    return _pen;
}

QVector<QPoint> Primitive::args() const
{
    return _args;
}

QVector<QPoint> Primitive::points() const
{
    return _points;
}

void Primitive::setArgs(QVector<QPoint> args)
{
    _args = args;
    setPoints(args);
    int x = 0, y = 0;

    for (QPoint p : args)
    {
        x += p.x();
        y += p.y();
    }
    int centerX = x / args.size();
    int centerY = y / args.size();
    _center = QPoint(centerX, centerY);
}

void Primitive::setPoints(QVector<QPoint> args)
{
    switch (_type)
    {
    case Primitive::Line:
        _points = drawLine(args);
        break;
    case Primitive::Polygon:
        break;
    case Primitive::Circle:
        _points = drawCircle(args);
        break;
    case Primitive::Rect:
        _points = drawRect(args);
        break;
    case Primitive::Ellipse:
        _points = drawEllipse(args);
        break;
    case Primitive::Curve:
    default:
        break;
    }
}

void Primitive::drawPrimitive(QImage &image)
{
    _pen.drawPixel(_points, image);
}

QVector<QPoint> Primitive::drawLine(QVector<QPoint> args)
{
    int x1 = args[0].x(), y1 = args[0].y(), x2 = args[1].x(), y2 = args[1].y();
    int dx = qAbs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = qAbs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2, e;
    QVector<QPoint> points;
    while (x1 != x2 || y1 != y2)
    {
        points.append(QPoint(x1, y1));
        e = err;
        if (e > -dx)
        {
            err -= dy;
            x1 += sx;
        }
        if (e < dy)
        {
            err += dx;
            y1 += sy;
        }
    }
    return points;
}

QVector<QPoint> Primitive::drawRect(QVector<QPoint> args)
{
    QVector<QPoint> points;
    if (args.size() < 2) return points;

    QPoint topLeft = args[0];
    QPoint bottomRight = args[1];

    QPoint topRight(bottomRight.x(), topLeft.y());
    QPoint bottomLeft(topLeft.x(), bottomRight.y());

    // Draw top edge
    points += drawLine({topLeft, topRight});
    // Draw right edge
    points += drawLine({topRight, bottomRight});
    // Draw bottom edge
    points += drawLine({bottomRight, bottomLeft});
    // Draw left edge
    points += drawLine({bottomLeft, topLeft});

    return points;
}

QVector<QPoint> Primitive::drawPolygon(QVector<QPoint> args)
{
    QVector<QPoint> points;
    return points;
}

void Primitive::setPen(QColor color, int brush_size)
{
    _pen.setBrushColor(color);
    _pen.setBrushSize(brush_size);
}

QVector<QPoint> Primitive::drawCircle(QVector<QPoint> args) {
    QVector<QPoint> points;
    if (args.size() < 2) return points;

    QPoint topLeft = args[0];
    QPoint bottomRight = args[1];

    // 计算圆心
    QPoint center((topLeft.x() + bottomRight.x()) / 2, (topLeft.y() + bottomRight.y()) / 2);

    // 计算半径
    int radius = qAbs(bottomRight.x() - topLeft.x()) / 2;

    int xc = center.x(), yc = center.y();
    int x = 0, y = radius;
    int d = 3 - 2 * radius;

    while (x <= y) {
        points.append(QPoint(xc + x, yc + y));
        points.append(QPoint(xc - x, yc + y));
        points.append(QPoint(xc + x, yc - y));
        points.append(QPoint(xc - x, yc - y));
        points.append(QPoint(xc + y, yc + x));
        points.append(QPoint(xc - y, yc + x));
        points.append(QPoint(xc + y, yc - x));
        points.append(QPoint(xc - y, yc - x));

        x++;
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
    }
    return points;
}
QVector<QPoint> Primitive::drawEllipse(QVector<QPoint> args)
{
    QVector<QPoint> points;
    if (args.size() < 2)
        return points;

    int xc = (args[0].x() + args[1].x()) / 2;
    int yc = (args[0].y() + args[1].y()) / 2;
    int a = qAbs(args[1].x() - args[0].x()) / 2;
    int b = qAbs(args[1].y() - args[0].y()) / 2;

    int x = 0, y = b;
    int a2 = a * a, b2 = b * b;
    int d1 = b2 - a2 * b + 0.25 * a2;
    int dx = 2 * b2 * x;
    int dy = 2 * a2 * y;

    // Region 1
    while (dx < dy)
    {
        points.append(QPoint(xc + x, yc + y));
        points.append(QPoint(xc - x, yc + y));
        points.append(QPoint(xc + x, yc - y));
        points.append(QPoint(xc - x, yc - y));

        if (d1 < 0)
        {
            x++;
            dx = dx + 2 * b2;
            d1 = d1 + dx + b2;
        }
        else
        {
            x++;
            y--;
            dx = dx + 2 * b2;
            dy = dy - 2 * a2;
            d1 = d1 + dx - dy + b2;
        }
    }

    // Region 2
    int d2 = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y >= 0)
    {
        points.append(QPoint(xc + x, yc + y));
        points.append(QPoint(xc - x, yc + y));
        points.append(QPoint(xc + x, yc - y));
        points.append(QPoint(xc - x, yc - y));

        if (d2 > 0)
        {
            y--;
            dy = dy - 2 * a2;
            d2 = d2 + a2 - dy;
        }
        else
        {
            y--;
            x++;
            dx = dx + 2 * b2;
            dy = dy - 2 * a2;
            d2 = d2 + dx - dy + a2;
        }
    }

    return points;
}
QVector<QPoint> Primitive::drawCurve(QVector<QPoint> args)
{
    QVector<QPoint> points;
    return points;
}

QVector<QPoint> Primitive::translate(QPoint pos)
{
    QVector<QPoint> args = _args;
    return args;
}

QVector<QPoint> Primitive::rotate(float r)
{
    QVector<QPoint> args = _args;
    return args;
}

QVector<QPoint> Primitive::scale(float s)
{
    QVector<QPoint> args = _args;
    return args;
}

QVector<QPoint> Primitive::clip(QPoint lt, QPoint rb)
{
    QVector<QPoint> args = _args;
    return args;
}
