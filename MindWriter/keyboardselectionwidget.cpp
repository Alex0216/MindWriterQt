#include "keyboardselectionwidget.h"
#include "keyboardwidget.h"
#include "mainwindow.h"

using namespace std;

KeyboardSelectionWidget::KeyboardSelectionWidget(QWidget *parent):
    QWidget(parent)
{
    //Keyboard layout selection
    keyboardLayoutSelection = new QComboBox(this);
    keyboardLayoutSelection->addItem("QWERTY");
    keyboardLayoutSelection->addItem("AZERTY");
    keyboardLayoutSelection->show();

    //Frame
    QLabel *labelSelection = new QLabel("Please choose a keyboard layout");
    frameSelection = new QVBoxLayout();
    frameSelection->addWidget(labelSelection);
    frameSelection->addWidget(keyboardLayoutSelection);

    //Buttons
    select = new QPushButton("Select", this);
    connect(select, SIGNAL(clicked()), this, SLOT(mainWindow()));

    quit = new QPushButton("Quit", this);
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    buttons = new QHBoxLayout();
    buttons->addWidget(select);
    buttons->addWidget(quit);

    //Window layout
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(frameSelection);
    mainLayout->addLayout(buttons);
}

QString KeyboardSelectionWidget::getChoice()
{
    return choice;
}

void KeyboardSelectionWidget::mainWindow()
{
    choice = keyboardLayoutSelection->currentText();
    this->close();
}


