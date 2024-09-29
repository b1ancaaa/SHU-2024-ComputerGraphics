#include "mainwindow.h"
#include <qnamespace.h>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      state(Line),
      primitive(nullptr),
      pen(Qt::black, 1) {
  ui->setupUi(this);
  image = QImage(this->size(), QImage::Format_ARGB32);
  image.fill(Qt::white);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  painter.begin(&image);

  foreach (Primitive *p, primitives) {
    p->setPen(Qt::red, 5);
    p->drawPrimitive(image);
  }
  painter.end();

  // 更新 QLabel 的 pixmap
  ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  QPoint pos = event->pos();
  points.append(pos);
  switch (state) {
    case Line:
      primitive = new Primitive(pen, Primitive::Line, {pos, pos});
      qDebug("setup a new prtmitive");
      primitives.append(primitive);
      break;
    default:
      break;
  }
  update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  QPoint pos = event->pos();
  //   QVector<QPoint> args;
  switch (state) {
    case Line:
      primitive->setArgs({points[0], pos});
      break;
    default:
      break;
  }
  update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  QPoint pos = event->pos();
  //   QVector<QPoint> args;
  switch (state) {
    case Line:
      primitive->setArgs({points[0], pos});
      break;
    default:
      break;
  }

  update();
  points.clear();
}
