#include <QApplication>
#include <iostream>

#include "Primitive.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Primitive p;
    std::cout << p.type();
    w.show();
    return a.exec();
}
