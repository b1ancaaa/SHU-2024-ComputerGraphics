#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QString>
#include <QUrl>
#include "Primitive.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    enum State {Line, Triangle, Rectangle, Circle, Ellipse, Polygon, Curve,
                 Translate, Rotate, Clip} state;
    QVector<QPoint> points;
    QList<Primitive *> primitives;
    Primitive *primitive;
    QImage image;
    QPainter painter;
    Pen pen;
    QString s;
};
#endif // MAINWINDOW_H
