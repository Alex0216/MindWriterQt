//#include "mainwindow.h"
#include "keyboardwidget.h"
#include "predictionwidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QTextEdit>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PredictionWidget *p = new PredictionWidget();
    KeyboardWidget *k = new KeyboardWidget;
    QTextEdit *t = new QTextEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(t);
    mainLayout->addWidget(p);
    mainLayout->addWidget(k);

    QWidget mainWindow;
    mainWindow.setLayout(mainLayout);
    mainWindow.show();
    return a.exec();
}
