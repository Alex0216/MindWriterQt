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


class KeyboardWidget : public QWidget, public Flashable
{
    Q_OBJECT
public:
    /*!
     * \brief Create a KeyboardWidget consisting of a 10*5 grid of
     *  QLabel meant to look like a keyboard
     *  The Qwerty layout is loaded by default
     * \param parent
     */
    explicit KeyboardWidget(QWidget *parent = 0);

    /*!
     * \brief Set the palette of the choosen QLabel to labelActifPalette
     * \param row
     * \param column
     */
    virtual void labelOn(int row, int column);

    /*!
     * \brief Set the palette of the choosen QLabel to labelInactifPalette
     * \param row
     * \param column
     */
    virtual void labelOff(int row, int column);
    void setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff,
                        QColor labelOff, QColor background);


    static const int KEYBOARD_WIDTH = 10;
    static const int KEYBOARD_HEIGHT = 5;
    static const int DELAY = 300;

signals:

    
public slots:
    void update();
    void layoutUpdate(QString layout);

private:
    QVector<QLabel* > keys;
    QPalette labelInactifPalette;
    QPalette labelActifPalette;
    QPalette backgroundPalette;
    QTimer timer;
    QMessageBox ErrorMessage;
    int updateRow;
    int updateColumn;
    QGridLayout *grid;
    
};

#endif // KEYBOARDWIDGET_H
