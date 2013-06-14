//#include "mainwindow.h"
#include "keyboardwidget.h"
#include "predictionwidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PredictionWidget *p = new PredictionWidget();
    KeyboardWidget *k = new KeyboardWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(p);
    mainLayout->addWidget(k);

    QWidget mainWindow;
    mainWindow.setLayout(mainLayout);
    mainWindow.show();
    return a.exec();
}
