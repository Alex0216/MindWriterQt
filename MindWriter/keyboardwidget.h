/**
 * \file keyboardwidget.h \version 1.1
 * \class KeyboardWidget
 * \author Alexandre St-Onge, Julien Aymong
 *
 * \brief A Widget meant to represent a keyboard
 * Each label has a minimum size of 90x90
 *
 * © TheBCIProject
 */
#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <string>
#include <fstream>

#include <QLabel>
#include <QMessageBox>
#include <QString>

#include "flashablewidget.h"
#include "keyboardselectionwidget.h"

class KeyboardWidget :public FlashableWidget
{
public:
    /*!
     * \brief Create a KeyboardWidget consisting of a grid of
     *  QLabel meant to look like a keyboard
     *  The Qwerty layout is loaded by default
     * \param width the number of column for this widget
     * \param height the number of row for this widget
     * \param parent
     */
    KeyboardWidget(int width, int height, QWidget *parent = 0);

signals:

    
public slots:
    /**
     * @brief Slot called to update the layout of the KeyboardWidget
     * @param layout
     */
    void layoutUpdate(QString layout);

private:

};

#endif // KEYBOARDWIDGET_H
