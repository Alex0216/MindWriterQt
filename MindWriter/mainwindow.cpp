/**
 * \file mainwindow.cpp \version 1.1
 * \author Alexandre St-Onge, Julien Aymong
 *
 *
 * \brief Implementation of the  MainWindow class
 */

#include "mainwindow.h"


MainWindow::MainWindow(QMainWindow *parent) :
    QMainWindow(parent)
{
    createActions();

    predictionW = new PredictionWidget(4, 1);
    predictionW->setColorScheme(defaultColorScheme::LETTER_ON,
                              defaultColorScheme::LABEL_ON,
                              defaultColorScheme::LETTER_OFF,
                              defaultColorScheme::LABEL_OFF,
                              defaultColorScheme::BACKGROUND);


    keyboardW = new KeyboardWidget(10,5);
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
    keyboardMenu = settingMenu->addMenu(tr("&Layout"));
    keyboardMenu->addAction(qwertyAct);
    keyboardMenu->addAction(azertyAct);
    flashMenu_ = settingMenu->addMenu(tr("&Flash Pattern"));
    flashMenu_->addAction(oneByOneAct);
    flashMenu_->addAction(binarySearchAct);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(mainLayout);

    flashMode_ = BinarySearch;

    /**
      * Setting up the timer
      */
    timer_.setInterval(DELAY);
    timer_.start();
    connect(&timer_, SIGNAL(timeout()), this, SLOT(updateFlash()));
    flashIndex_ = 0;
    currentWidget_ = keyboardW;

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
    debouncer_ = true;
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
    keyboardW->binarySearch();

}


void MainWindow::selectQWERTYKeyboardLayout()
{
    keyboardW->layoutUpdate("qwerty.txt");
}

void MainWindow::selectAZERTYKeyboardLayout()
{
    keyboardW->layoutUpdate("azerty.txt");
}

void MainWindow::selectOneByOneFlashOption()
{
    if(flashMode_ != OneByOne)
    {
        flashMode_ = OneByOne;
        predictionW->reset();
        keyboardW->reset();
        currentWidget_ = predictionW;
        flashIndex_ = 0;
        // Might need more resetting here...
    }
}

void MainWindow::selectBinarySearchFlashOption()
{
    if(flashMode_ != BinarySearch)
    {
        flashMode_ = BinarySearch;
        predictionW->reset();
        keyboardW->reset();
        currentWidget_ = keyboardW;
        //Might need more resetting here
    }
}

void MainWindow::createActions()
{
    /**
     * Setting the menu for the keyboard layout
     */
    QActionGroup* layoutGroup = new QActionGroup(this);
    qwertyAct = new QAction(tr("&QWERTY"), this);
    qwertyAct->setStatusTip(tr("Choose the QWERTY keyboard layout"));
    qwertyAct->setCheckable(true);
    qwertyAct->setChecked(true); ///< By default the qwerty layout is loaded
    connect(qwertyAct, SIGNAL(triggered()), this, SLOT(selectQWERTYKeyboardLayout()));

    azertyAct = new QAction(tr("&AZERTY"), this);
    //selectKeyboardAct->setShortcuts(QKeySequence::New);
    azertyAct->setStatusTip(tr("Choose the AZERTY keyboard layout"));
    azertyAct->setCheckable(true);
    connect(azertyAct, SIGNAL(triggered()), this, SLOT(selectAZERTYKeyboardLayout()));

    qwertyAct->setActionGroup(layoutGroup);
    azertyAct->setActionGroup(layoutGroup);
    //**************************************************

    /**
     * Setting the menu for the flash option
     */
    QActionGroup* flashGroup = new QActionGroup(this);
    oneByOneAct = new QAction(tr("&One by one"), this);
    oneByOneAct->setStatusTip(tr("Flashes the label one after the other"));
    oneByOneAct->setCheckable(true);
    connect(oneByOneAct, SIGNAL(triggered()), this, SLOT(selectOneByOneFlashOption()));

    binarySearchAct = new QAction(tr("&Binary Search"), this);
    binarySearchAct->setStatusTip(tr("divide ut regnes"));
    binarySearchAct->setCheckable(true);
    binarySearchAct->setChecked(true);
    connect(binarySearchAct, SIGNAL(triggered()), this, SLOT(selectBinarySearchFlashOption()));

    oneByOneAct->setActionGroup(flashGroup);
    binarySearchAct->setActionGroup(flashGroup);

}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_Space && debouncer_)
    {
        timer_.stop();
        debouncer_ = false;
        switch(flashMode_)
        {
         case OneByOne:
            if(!currentWidget_->getActiveLabelsContent().isEmpty())
            {
               updateTextEdit();
            }
            break;
        case BinarySearch:
            if(currentWidget_->selectHalve())
                // selectHalve() return true when the halve has a size on 1, meaning
                // the search is done
            {
                updateTextEdit();
            }
            break;
        }
        timer_.start();
    }
}

void MainWindow::updateTextEdit()
{
    QString string = currentWidget_->getActiveLabelsContent().first();

    //translate special char like space and newline
    if(string == "˽")
        string = ' ';
    else if (string == "↲")
        string  = '\n';

    //if string is backspace, remove one char from the textEdit
    if (string == "←" && !textEdit->toPlainText().isEmpty())
    {
        int size = textEdit->toPlainText().size();
        textEdit->setText(QString::fromStdString(textEdit->toPlainText().toStdString().substr(0, size -1)));
    }
    else
        textEdit->setText(textEdit->toPlainText() + string);

}
