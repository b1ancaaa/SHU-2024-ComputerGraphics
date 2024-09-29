#include "Pen.h"

Pen::Pen()
{
    brush_color = Qt::black;
    setBrushSize(1);
}

Pen::Pen(QColor color, int brush_type)
{
    brush_color = color;
    setBrushSize(brush_type);
}

void Pen::setBrushColor(QColor color)
{
    brush_color = color;
}

void Pen::drawPixel(QList<QPoint> points, QImage &image)
{
    int brush_half_size = brush_size.size() / 2;
    for (auto pos : points)
    {
        for (int i = 0; i < brush_size.size(); i++)
        {
            for (int j = 0; j < brush_size.size(); j++)
            {
                if (brush_size.at(i).at(j) == 1)
                {
                    int x = pos.x() + i - brush_half_size;
                    int y = pos.y() + j - brush_half_size;
                    if (x >= 0 && x < image.width() && y >= 0 && y < image.height())
                    {
                        image.setPixelColor(x, y, brush_color);
                    }
                }
            }
        }
    }
}

void Pen::setBrushSize(int size)
{
    if (size > 0)
    {
        brush_size = generateSquareBrush(size);
    }
    else
    {
        brush_size = generateCircularBrush(-size);
    }
}

QVector<QVector<int>> Pen::generateCircularBrush(int size)
{
    QVector<QVector<int>> brush(2 * size + 1, QVector<int>(2 * size + 1, 0));
    for (int dx = -size; dx <= size; ++dx)
    {
        for (int dy = -size; dy <= size; ++dy)
        {
            if (dx * dx + dy * dy <= size * size)
            {
                brush[dx + size][dy + size] = 1;
            }
        }
    }
    return brush;
}

QVector<QVector<int>> Pen::generateSquareBrush(int size)
{
    QVector<QVector<int>> brush(2 * size + 1, QVector<int>(2 * size + 1, 1));
    return brush;
}
