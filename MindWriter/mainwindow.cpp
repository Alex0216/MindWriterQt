#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
{


    predictionW = new PredictionWidget();
    predictionW->setColorScheme(defaultColorScheme::LETTER_ON,
                              defaultColorScheme::LABEL_ON,
                              defaultColorScheme::LETTER_OFF,
                              defaultColorScheme::LABEL_OFF,
                              defaultColorScheme::BACKGROUND);


    keyboardW = new KeyboardWidget();
    keyboardW->setColorScheme(defaultColorScheme::LETTER_ON,
                              defaultColorScheme::LABEL_ON,
                              defaultColorScheme::LETTER_OFF,
                              defaultColorScheme::LABEL_OFF,
                              defaultColorScheme::BACKGROUND);

    textEdit = new QTextEdit();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(predictionW);
    mainLayout->addWidget(keyboardW);



    //MenuBar
    menuBar()->addMenu("File");
    menuBar()->addMenu("Edit");
    menuBar()->addMenu("Configuration");

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(mainLayout);
}
