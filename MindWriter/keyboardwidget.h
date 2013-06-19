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


class KeyboardWidget : public QWidget, public FlashableInterface
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

    /**
     * @brief getNumberOfLabels
     * @return the number of QLabels in the widget
     */
    int getNumberOfLabels() const;

    /**
     * @brief Flashes the label one by one
     * @return true when all the labels has been flashed once
     * @return false otherwise
     */
    bool oneByOneSearch();

    /**
     * @brief Flashes the label in a binary search like pattern
     * @return true when the search has reach the end
     * @return false otherwise
     */
    bool binarySearch();

    /**
     * @brief getActiveLabelsContent
     * @return QVector containing the content of all the
     * active labels
     */
    QVector<std::string> getActiveLabelsContent();

    /**
     * @brief turn all label off
     */
    void allOff();

    /**
     * @brief turn all label on
     */
    void allOn();

    static const int KEYBOARD_WIDTH = 10;
    static const int KEYBOARD_HEIGHT = 5;

signals:

    
public slots:
    void layoutUpdate(QString layout);

private:
    QVector<QLabel* > keys;
    QVector<QLabel*> activeKeys;
    QPalette labelInactifPalette;
    QPalette labelActifPalette;
    QPalette backgroundPalette;
    QMessageBox ErrorMessage;
    QGridLayout *grid;
    
};

#endif // KEYBOARDWIDGET_H
