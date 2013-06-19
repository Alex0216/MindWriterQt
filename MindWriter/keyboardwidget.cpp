#include "keyboardwidget.h"
#include "keyboardselectionwidget.h"
#include <string>
#include <fstream>

using namespace std;

KeyboardWidget::KeyboardWidget(QWidget *parent) :
    QWidget(parent), labelInactifPalette(), labelActifPalette()
{
    keys = QVector<QLabel*>();
    grid = new QGridLayout;

    ifstream keyboardLayout;
    keyboardLayout.open("qwerty.txt");
    if(keyboardLayout.fail())
    {
        //If the layout isn't working
        ErrorMessage.setWindowTitle("Error");
        ErrorMessage.setIcon(QMessageBox::Critical);
        ErrorMessage.setText("Can't load the keyboard layout!");
        ErrorMessage.show();
    }
    else
    {
        QFont f("Helvetica", 20);
        for (int row = 0; row < KEYBOARD_HEIGHT; ++row )
        {
            for(int column = 0; column < KEYBOARD_WIDTH; ++column)
            {
                string keyboardKey;
                keyboardLayout >> keyboardKey;
                QLabel *key = new QLabel(QString::fromStdString(keyboardKey));
                key->setFont(f);
                key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
                key->setMinimumWidth(90);
                key->setMinimumHeight(90);
                key->setScaledContents(true);
                key->setFrameShape(QFrame::Box);
                key->setLineWidth(3);
                key->setAlignment(Qt::AlignCenter);
                key->setPalette(labelInactifPalette);
                key->setAutoFillBackground(true);
                grid->addWidget(key, row, column);
                keys.push_back(key);
            }
        }

        setLayout(grid);
    }

}

void KeyboardWidget::layoutUpdate(QString layout)
{

    ifstream keyboardLayout;
    keyboardLayout.open(layout.toStdString());
    if(keyboardLayout.fail())
    {
        //If the layout isn't working
        ErrorMessage.setWindowTitle("Error");
        ErrorMessage.setIcon(QMessageBox::Critical);
        ErrorMessage.setText("Can't load the keyboard layout!");
        ErrorMessage.show();
    }
    else
    {
        for (int i = 0; i < KEYBOARD_WIDTH*KEYBOARD_HEIGHT; ++i )
        {
                string keyboardKey;
                keyboardLayout >> keyboardKey;
                keys[i]->setText(QString::fromStdString(keyboardKey));
        }
    }

}

void KeyboardWidget::labelOn(int row, int column)
{
    int index = column + row*KEYBOARD_WIDTH;
    QLabel* label = keys.at(index);
    label->setPalette(labelActifPalette);
    activeKeys.push_back(label);

}

void KeyboardWidget::labelOff(int row, int column)
{
    int index = column + row*KEYBOARD_WIDTH;
    QLabel* label = keys.at(index);
    label->setPalette(labelInactifPalette);
    activeKeys.remove(activeKeys.indexOf(label));

}

void KeyboardWidget::setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff, QColor labelOff, QColor background)
{
    /*
     *Palette pour les label Inactifs
     * Texte blanc/gris et fond noir-ish
     */

    //Texte blanc
    QBrush brushInactif1;
    brushInactif1.setColor(letterOff);
    brushInactif1.setStyle(Qt::SolidPattern);

    //Background noir
    QBrush brushInactif2;
    brushInactif2.setColor(labelOff);
    brushInactif2.setStyle(Qt::SolidPattern);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushInactif1);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushInactif1);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::Window, brushInactif2);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushInactif2);

    /*
     *Palette pour les label Actifs
     * Texte noir et fond blanc
     */
    //Texte noir
    QBrush brushActif1;
    brushActif1.setColor(letterOn);
    brushActif1.setStyle(Qt::SolidPattern);

    //Background Blanc
    QBrush brushActif2;
    brushActif2.setColor(QColor(labelOn));
    brushActif2.setStyle(Qt::SolidPattern);

    labelActifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushActif1);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushActif1);

    labelActifPalette.setBrush(QPalette::Active, QPalette::Window, brushActif2);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushActif2);

    /*
     *Palette pour le background
     *noir-ish
     */
    QBrush brushBack1(background);
    QBrush brushBack2(background);

    backgroundPalette.setBrush(QPalette::Active, QPalette::Window, brushBack1);
    backgroundPalette.setBrush(QPalette::Inactive, QPalette::Window, brushBack2);

    //----------------------------------------------------------------------

    setPalette(backgroundPalette);
    setAutoFillBackground(true);

    for (int i = 0; i < keys.size(); ++i )
    {
        keys.at(i)->setPalette(labelInactifPalette);
    }
}

int KeyboardWidget::getNumberOfLabels() const
{
    return keys.size();
}

bool KeyboardWidget::oneByOneSearch()
{
    static int index = 0;

    QLabel* lastLabel;
    if(index == 0)
        lastLabel = keys.last();
    else
        lastLabel = keys.at(index-1);

    lastLabel->setPalette(labelInactifPalette);
    if(activeKeys.contains(lastLabel))
        activeKeys.remove(activeKeys.indexOf(lastLabel));

    if( index != keys.size())
    {
        activeKeys.push_back(keys.at(index));
        keys.at(index++)->setPalette(labelActifPalette);
    }
    else
    {
        index = 0;
        return true;
    }

    return false;

}

bool KeyboardWidget::binarySearch()
{
    return false;
}

QVector<string> KeyboardWidget::getActiveLabelsContent()
{
    QVector<string> contents;
    for_each(activeKeys.begin(),activeKeys.end(), [&contents] (QLabel* l){
        contents.push_back(l->text().toStdString());
    } );
    return contents;
}

void KeyboardWidget::allOff()
{
    for (int i = 0; i < keys.size(); ++i)
    {
        keys.at(i)->setPalette(labelInactifPalette);
    }
    activeKeys.clear();
}

void KeyboardWidget::allOn()
{
    for (int i = 0; i < keys.size(); ++i)
    {
        QLabel* label = keys.at(i);
        if(!activeKeys.contains(label))
        {
            label->setPalette(labelActifPalette);
            activeKeys.push_back(label);
        }
    }

}

