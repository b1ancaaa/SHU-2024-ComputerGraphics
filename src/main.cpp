#include <QApplication>
#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include<iostream>
#include "primitives.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  QMainWindow mainWindow;
  Primitives *p = new Primitives(&mainWindow);
  mainWindow.setCentralWidget(p);
  mainWindow.resize(800, 600);
  mainWindow.show();
  int t;
  std::cin >>t;
  p->setBrush(t);
  p->drawLine(100, 100, 150, 200, Qt::black);
//   p->setBrush(3);
  p->drawRect(300, 100, 400, 200, Qt::blue);
//   p->setBrush(1);
  p->drawCircle(100, 300, 50, Qt::green);
  p->drawEllipse(400, 300, 200, 100, Qt::red);

  return app.exec();
}