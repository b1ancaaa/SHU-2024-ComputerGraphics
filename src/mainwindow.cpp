#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , state(Rectangle)
    , primitive(nullptr)
    , pen(Qt::black, 2)
{
    ui->setupUi(this);
    image = QImage(this->size(), QImage::Format_RGBA64);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event);
    painter.begin(&image);
    image.fill(Qt::white);
    foreach (Primitive *p, primitives)
    {
        p->setPen(Qt::red, -3);
        p->drawPrimitive(image);
    }
    painter.end();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx()-=10;
    pos.ry()-=40;
    points.append(pos);
    switch (state) {
    case Line:
        primitive = new Primitive(pen, Primitive::Line,{pos, pos});
        qDebug("setup a new prtmitive");
        primitives.append(primitive);
        break;
    case Circle:
        primitive = new Primitive(pen, Primitive::Circle,{pos, pos});
        primitives.append(primitive);
        break;
    case Rectangle:
        primitive = new Primitive(pen, Primitive::Rect,{pos, pos});
        qDebug("setup a new prtmitive");
        primitives.append(primitive);
        break;
    case Ellipse:
        primitive = new Primitive(pen, Primitive::Ellipse,{pos, pos});
        qDebug("setup a new prtmitive");
        primitives.append(primitive);
    default:
        break;
    }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx()-=10;
    pos.ry()-=40;
    switch (state) {
    case Line:
        primitive->setArgs({points[0], pos});
        break;
    case Circle:
        primitive->setArgs({points[0], pos});
        break;
    case Rectangle:
        primitive->setArgs({points[0], pos});
        break;
    case Ellipse:
        primitive->setArgs({points[0], pos});
        break;
    default:
        break;
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint pos = event->pos();
    pos.rx()-=10;
    pos.ry()-=40;
    switch (state) {
    case Line:
        primitive->setArgs({points[0], pos});
        break;
    case Circle:
        primitive->setArgs({points[0], pos});
        break;
    case Rectangle:
        primitive->setArgs({points[0], pos});
        break;
    case Ellipse:
        primitive->setArgs({points[0], pos});
        break;
    default:
        break;
    }

    update();
    points.clear();
}


void MainWindow::on_Circle_clicked()
{
    state=Circle;
    points.clear();
}

void MainWindow::on_Line_clicked()
{
    state=Line;
    points.clear();
}

void MainWindow::on_Rectangle_clicked(){
    state=Rectangle;
    points.clear();
}


void MainWindow::on_BzeierCurve_clicked()
{
    state=BeizerCurve;
    points.clear();
}

void MainWindow::on_Ellipse_clicked()
{
    state=Ellipse;
    points.clear();
}

