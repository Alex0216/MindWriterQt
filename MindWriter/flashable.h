#ifndef FLASHABLE_H
#define FLASHABLE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QVector>

class Flashable: public QWidget
{
    Q_OBJECT
public:
    Flashable(int width, int height, QWidget *parent=0);
    virtual ~Flashable() {}
    virtual void setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff,
                                QColor labelOff, QColor background);

    /*!
     * \brief Set the palette of the choosen QLabel to labelActifPalette
     * \param row: the x coordinate of the label
     * \param column: the y coordinate of the label
     */
    void labelOn(int row, int column);

    /*!
     * \brief Set the palette of the choosen QLabel to labelInactifPalette
     * \param row: the x coordinate of the label
     * \param column: the y coordinate of the label
     */
    void labelOff(int row, int column);

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
    virtual bool oneByOneSearch();

    /**
     * @brief Flashes the label in a binary search like pattern
     * @return true when the search has reach the end
     * @return false otherwise
     */
    virtual bool binarySearch();

    /**
     * @brief getActiveLabelsContent
     * @return QVector containing the content of all the
     * active labels
     */
    virtual QVector<QString> getActiveLabelsContent() const;

    /**
     * @brief select the halve currently flashing when in a binarySearch()
     * @return true if the selected halve contains 1 label
     * @return false otherwise
     */
    virtual bool selectHalve();

    /**
     * @brief turn all label off
     */
    void allOff();

    /**
     * @brief turn all label on
     */
    void allOn();

protected:
    /**
     * QVector containing all the QLabels of the widget
     */
    QVector<QLabel* > vLabels_;

private:
    int width_;
    int height_;
    QVector<QLabel*> vActiveLabels_;
    QPalette inactiveLabelPalette;
    QPalette activeLabelPalette;
    QPalette backgroundPalette;
    QGridLayout *grid;

    QVector<QLabel*> vFirstHalve_;
    QVector<QLabel*> vSecondHalve_;
    QVector<QLabel*> vSelectedHalve_;
    int currentHalve;
    int selectedHalveWidth;
    int selectedHalveHeight;
    int firstHalveWidth;
    int firstHalveHeight;
    int secondHalveWidth;
    int secondHalveHeight;

};

#endif // FLASHABLE_H
