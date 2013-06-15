#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{


    predictionW = new PredictionWidget();

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

    setLayout(mainLayout);
}
