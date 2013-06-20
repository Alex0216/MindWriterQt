#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QTimer>
#include <QMessageBox>
#include <QString>

#include "flashable.h"


class KeyboardWidget :public Flashable
{
public:
    /*!
     * \brief Create a KeyboardWidget consisting of a 10*5 grid of
     *  QLabel meant to look like a keyboard
     *  The Qwerty layout is loaded by default
     * \param parent
     */
    explicit KeyboardWidget(int row, int column, QWidget *parent = 0);

signals:

    
public slots:
    void layoutUpdate(QString layout);

private:
    QMessageBox ErrorMessage;
};

#endif // KEYBOARDWIDGET_H
