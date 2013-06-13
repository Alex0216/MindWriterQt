//#include "mainwindow.h"
#include "keyboardwidget.h"
#include <QApplication>
#include <iostream>


#define DELAY

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyboardWidget k;
    k.show();
    return a.exec();
}
