#include <QApplication>

#include "mainwindow.h"
#include "parser.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowState(Qt::WindowFullScreen);
    w.show();

    return a.exec();
}
