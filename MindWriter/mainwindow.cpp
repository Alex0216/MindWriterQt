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

