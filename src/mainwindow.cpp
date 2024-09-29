#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), state(Line), primitive(nullptr), pen(Qt::black, 1)
{
    ui->setupUi(this);
    image = QImage(this->size(), QImage::Format_ARGB32);
    image.fill(Qt::white);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    painter.begin(&image);

    foreach (Primitive *p, primitives)
    {
        p->setPen(Qt::red);
        p->drawPrimitive(image);
    }
    painter.end();

    // 更新 QLabel 的 pixmap
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx() -= 10;
    pos.ry() -= 40;
    points.append(pos);
    switch (state)
    {
    case Line:
        primitive = new Primitive(pen, Primitive::Line, {pos, pos});
        qDebug("setup a new prtmitive");
        primitives.append(primitive);
        break;
    case Circle:
        primitive = new Primitive(pen, Primitive::Circle, {pos, QPoint(0, 0)});
        primitives.append(primitive);
        break;
        break;
    default:
        break;
    }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx() -= 10;
    pos.ry() -= 40;
    QVector<QPoint> args;
    switch (state)
    {
    case Line:
        primitive->setArgs({points[0], pos});
        break;
    case Circle:
        if (qAbs(pos.x() - points[0].x()) < qAbs(pos.y() - points[0].y()))
            if (pos.ry() > points[0].y())
                pos.ry() = points[0].y() + qAbs(pos.rx() - points[0].x());
            else
                pos.ry() = points[0].y() - qAbs(pos.rx() - points[0].x());
        else if (pos.rx() > points[0].x())
            pos.rx() = points[0].x() + qAbs(pos.ry() - points[0].y());
        else
            pos.rx() = points[0].x() - qAbs(pos.ry() - points[0].y());
        primitive->setArgs({(pos + points[0]) / 2, (pos - points[0]) / 2});
        break;
    default:
        break;
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx() -= 10;
    pos.ry() -= 40;
    QVector<QPoint> args;
    switch (state)
    {
    case Line:
        primitive->setArgs({points[0], pos});
        break;
    case Circle:
        if (qAbs(pos.x() - points[0].x()) < qAbs(pos.y() - points[0].y()))
            if (pos.ry() > points[0].y())
                pos.ry() = points[0].y() + qAbs(pos.rx() - points[0].x());
            else
                pos.ry() = points[0].y() - qAbs(pos.rx() - points[0].x());
        else if (pos.rx() > points[0].x())
            pos.rx() = points[0].x() + qAbs(pos.ry() - points[0].y());
        else
            pos.rx() = points[0].x() - qAbs(pos.ry() - points[0].y());
        primitive->setArgs({(pos + points[0]) / 2, (pos - points[0]) / 2});
        break;
    default:
        break;
    }

    update();
    points.clear();
}

void MainWindow::on_Circle_clicked()
{
    state = Circle;
    points.clear();
}

void MainWindow::on_Line_clicked()
{
    state = Line;
    points.clear();
}

void MainWindow::on_BzeierCurve_clicked()
{
    state = BeizerCurve;
    points.clear();
}
