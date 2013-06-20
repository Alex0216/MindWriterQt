#include "keyboardwidget.h"
#include "keyboardselectionwidget.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

KeyboardWidget::KeyboardWidget(int width, int height, QWidget *parent):
    Flashable(width, height, parent)
{

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
        //If the layout isn't working
        ErrorMessage.setWindowTitle("Error");
        ErrorMessage.setIcon(QMessageBox::Critical);
        ErrorMessage.setText("Can't load the keyboard layout!");
        ErrorMessage.show();
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


