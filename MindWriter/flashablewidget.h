/**
 * flashablewidget.h \version 1.1
 * \class FlashableWidget
 * \author Alexandre St-Onge
 * \brief A Widget containing a grid of QLabel
 * that can be flashed to be use with a BCI*
 */

#ifndef FLASHABLE_H
#define FLASHABLE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPalette>
#include <QVector>

class FlashableWidget: public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for FlashableWidget
     * @param width number of column
     * @param height number of row
     * @param parent the widget's parent
     *
     * The labels are initialize with an empty string,
     * the font is set to Helvetica, size 20.
     * The frameShape is QFrame::Box
     * The alignment is Qt::AlignCenter
     */
    FlashableWidget(int width, int height, QWidget *parent=0);

    /**
     * @brief destructor, does nothing
     */
    virtual ~FlashableWidget() {}

    /**
     * @brief Set the color scheme for the widget
     * @param letterOn color when the letter is on (flashing)
     * @param labelOn color for the label's background when on
     * @param letterOff color when the letter is off
     * @param labelOff color for the label's background when off
     * @param background color for the widget's background
     */
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
     * @brief Returns the number of QLabel in the widget
     * @return the number of QLabels in the widget
     */
    int getNumberOfLabels() const;

    /**
     * @brief Flashes the labels one by one
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
     * @brief Return a QVector of QString containing all of
     * the text of the active QLabel
     * A QLabel is active when it's flashing
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

    /**
     * @brief reset the state of both oneByOneSearch
     * and BinarySearch by setting oneByOneIndex_ to 0,
     * clearing vSelectedHalve then calling allOff();
     *
     */
    void reset();

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

    int oneByOneIndex_;

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
