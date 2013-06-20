/**
 * \file keyboardwidget.cpp \version 1.1
 * \author Alexandre St-Onge, Julien Aymong
 *
 * \brief Implementation of the KeyboardWidget class
 *
 * © TheBCIProject
 *
 */
#include "keyboardwidget.h"

using namespace std;

KeyboardWidget::KeyboardWidget(int width, int height, QWidget *parent):
    FlashableWidget(width, height, parent)
{

    ifstream keyboardLayout;
    keyboardLayout.open("qwerty.txt");
    if(keyboardLayout.fail())
    {
        QMessageBox errorMessage;
        //If the layout isn't working
        errorMessage.setWindowTitle("Error");
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.setText("Can't load the keyboard layout!");
        errorMessage.show();
    }
    else
    {
        for(int i = 0; i < vLabels_.size(); ++i)
        {
            string keyboardKey;
            keyboardLayout >> keyboardKey;
            QLabel *key = vLabels_.at(i);
            key->setText(QString::fromStdString(keyboardKey));
            key->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
            key->setMinimumWidth(90);
            key->setMinimumHeight(90);
        }
    }

}

void KeyboardWidget::layoutUpdate(QString layout)
{

    ifstream keyboardLayout;
    keyboardLayout.open(layout.toStdString());
    if(keyboardLayout.fail())
    {
        QMessageBox errorMessage;
        //If the layout isn't working
        errorMessage.setWindowTitle("Error");
        errorMessage.setIcon(QMessageBox::Critical);
        errorMessage.setText("Can't load the keyboard layout!");
        errorMessage.show();
    }
    else
    {
        for (int i = 0; i < vLabels_.size(); ++i )
        {
                string keyboardKey;
                keyboardLayout >> keyboardKey;
                vLabels_[i]->setText(QString::fromStdString(keyboardKey));
        }
    }

}


