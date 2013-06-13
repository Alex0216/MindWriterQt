#include "keyboardwidget.h"

KeyboardWidget::KeyboardWidget(QWidget *parent) :
    QWidget(parent)
{
    keys = new QVector<QLabel*>();
    QGridLayout *grid = new QGridLayout;

    /*
     *Palette pour les label Inactifs
     * Texte blanc/gris et fond noir-ish
     */
    labelInactifPalette = new QPalette();
    //Texte blanc
    QBrush brushInactif1;
    brushInactif1.setColor(QColor(255,255,255,130));
    brushInactif1.setStyle(Qt::SolidPattern);

    //Background noir
    QBrush brushInactif2;
    brushInactif2.setColor(QColor(40,40,40,200));
    brushInactif2.setStyle(Qt::SolidPattern);

    labelInactifPalette->setBrush(QPalette::Active, QPalette::WindowText, brushInactif1);
    labelInactifPalette->setBrush(QPalette::Inactive, QPalette::WindowText, brushInactif1);

    labelInactifPalette->setBrush(QPalette::Active, QPalette::Window, brushInactif2);
    labelInactifPalette->setBrush(QPalette::Inactive, QPalette::Window, brushInactif2);

    /*
     *Palette pour les label Actifs
     * Texte noir et fond blanc
     */
    labelActifPalette = new QPalette();
    //Texte noir
    QBrush brushActif1;
    brushActif1.setColor(QColor(0,0,0,255));
    brushActif1.setStyle(Qt::SolidPattern);

    //Background Blanc
    QBrush brushActif2;
    brushActif2.setColor(QColor(255,255,255,200));
    brushActif2.setStyle(Qt::SolidPattern);

    labelActifPalette->setBrush(QPalette::Active, QPalette::WindowText, brushActif1);
    labelActifPalette->setBrush(QPalette::Inactive, QPalette::WindowText, brushActif1);

    labelActifPalette->setBrush(QPalette::Active, QPalette::Window, brushActif2);
    labelActifPalette->setBrush(QPalette::Inactive, QPalette::Window, brushActif2);

    /*
     *Palette pour le background
     *noir-ish
     */
    backgroundPalette = new QPalette();

    QBrush brushBack1(QColor(50,50,50,200));
    QBrush brushBack2(QColor(10,10,10,255));

    backgroundPalette->setBrush(QPalette::Active, QPalette::Window, brushBack1);
    backgroundPalette->setBrush(QPalette::Inactive, QPalette::Window, brushBack2);

    //----------------------------------------------------------------------

    setPalette(*backgroundPalette);
    setAutoFillBackground(true);
    QFont f("Helvetica", 20);
    for (int row = 0; row < KEYBOARD_HEIGHT; ++row )
    {
        for(int column = 0; column < KEYBOARD_WIDTH; ++column)
        {
            QLabel *key = new QLabel("A");
            key->setFont(f);
            key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            key->setMinimumWidth(50);
            key->setMinimumHeight(50);
            key->setScaledContents(true);
            key->setFrameShape(QFrame::Box);
            key->setLineWidth(3);
            key->setAlignment(Qt::AlignCenter);
            key->setPalette(*labelInactifPalette);
            key->setAutoFillBackground(true);
            grid->addWidget(key, row, column);
            keys->push_back(key);
        }
    }

    setLayout(grid);

    // Setting the timer for the main loop
    timer.setInterval(500);
    timer.start();
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    updateRow = 0;
    updateColumn = 0;

}

void KeyboardWidget::update()
{
    // Turn off the last label
    labelOff(updateRow, updateColumn);

    ++updateColumn;
    if (updateColumn == KEYBOARD_WIDTH)
    {
        updateColumn = 0;
        updateRow++;
    }

    // Reset counter if needed
    if (updateRow == KEYBOARD_HEIGHT)
        updateRow = 0;


    labelOn(updateRow, updateColumn);


}

void KeyboardWidget::labelOn(int row, int column)
{
    int index = column + row*KEYBOARD_WIDTH;
    keys->at(index)->setPalette(*labelActifPalette);

}

void KeyboardWidget::labelOff(int row, int column)
{
    int index = column + row*KEYBOARD_WIDTH;
    keys->at(index)->setPalette(*labelInactifPalette);

}
