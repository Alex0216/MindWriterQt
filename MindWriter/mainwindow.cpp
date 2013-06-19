#include <iostream>

#include "mainwindow.h"
#include "keyboardselectionwidget.h"

MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
{
/*
    KeyboardSelectionWidget *test = new KeyboardSelectionWidget();
    test->show();
*/
    createActions();

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
    textEdit->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(predictionW);
    mainLayout->addWidget(keyboardW);



    //MenuBar
    fileMenu = menuBar()->addMenu(tr("&File"));
    editMenu = menuBar()->addMenu(tr("&Edit"));
    settingMenu = menuBar()->addMenu(tr("&Settings"));
    settingMenu->addAction(selectKeyboardAct);
    keyboardMenu = settingMenu->addMenu(tr("&Layout"));
    keyboardMenu->addAction(qwertyAct);
    keyboardMenu->addAction(azertyAct);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(mainLayout);

    flashMode_ = OneByOne;

    /**
      * Setting up the timer
      */
    timer_.setInterval(DELAY);
    timer_.start();
    connect(&timer_, SIGNAL(timeout()), this, SLOT(updateFlash()));
    flashIndex_ = 0;
    currentWidget_ = predictionW;

    binarySearchStep_ = 0;
    binarySearchSubStep_ = 0;

    //Fill vLabelCoordinate
    //For the PredictionWidget
    for(int i = 0; i < predictionW->getNumberOfLabels(); ++i)
        vLabelCoordinate.push_back(QPair<int, int>(0, i));
    //For the KeyboardWidget
    for(int row = 0; row < KeyboardWidget::KEYBOARD_HEIGHT; ++row)
        for (int column = 0; column < KeyboardWidget::KEYBOARD_WIDTH; ++column)
            vLabelCoordinate.push_back(QPair<int, int>(row, column));


}

void MainWindow::updateFlash()
{

    switch(flashMode_)
    {
    case OneByOne:
        oneByOneSearch();
        break;
    case BinarySearch:
        binarySearch();
        break;
    }
}

void MainWindow::oneByOneSearch()
{
    if(currentWidget_->oneByOneSearch())
    {
        flashIndex_++;
        currentWidget_ = keyboardW;
    }
    if( flashIndex_ == 2)
    {
        flashIndex_ = 0;
        currentWidget_ = predictionW;
    }
}

void MainWindow::binarySearch()
{
    predictionW->binarySearch();

}

void MainWindow::selectKeyboardLayout()
{
    KeyboardSelectionWidget *keyboardSelectionWidget = new KeyboardSelectionWidget();
    keyboardSelectionWidget->show();
}

void MainWindow::selectQWERTYKeyboardLayout()
{
    keyboardW->layoutUpdate("qwerty.txt");
}

void MainWindow::selectAZERTYKeyboardLayout()
{
    keyboardW->layoutUpdate("azerty.txt");
}

void MainWindow::createActions()
{
    selectKeyboardAct = new QAction(tr("&Keyboard layout"), this);
    //selectKeyboardAct->setShortcuts(QKeySequence::New);
    selectKeyboardAct->setStatusTip(tr("Choose the keyboard layout"));
    connect(selectKeyboardAct, SIGNAL(triggered()), this, SLOT(selectKeyboardLayout()));

    qwertyAct = new QAction(tr("&QWERTY"), this);
    //selectKeyboardAct->setShortcuts(QKeySequence::New);
    qwertyAct->setStatusTip(tr("Choose the QWERTY keyboard layout"));
    connect(qwertyAct, SIGNAL(triggered()), this, SLOT(selectQWERTYKeyboardLayout()));

    azertyAct = new QAction(tr("&AZERTY"), this);
    //selectKeyboardAct->setShortcuts(QKeySequence::New);
    azertyAct->setStatusTip(tr("Choose the AZERTY keyboard layout"));
    connect(azertyAct, SIGNAL(triggered()), this, SLOT(selectAZERTYKeyboardLayout()));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Space)
    {
        switch(flashMode_)
        {
         case OneByOne:
                if(!currentWidget_->getActiveLabelsContent().isEmpty())
                {
                    QString letter = currentWidget_->getActiveLabelsContent().first();
                    textEdit->setText(textEdit->toPlainText() + letter);
                }
                break;
        case BinarySearch:
            break;
        }
    }
}

