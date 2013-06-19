#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "flashable.h"

class PredictionWidget : public QWidget, public FlashableInterface
{
    Q_OBJECT
public:
    /*!
     * \brief Create a PredictionWidget consisting of 1 line of
     *  4 Qlabel
     * \param parent
     *  Create a PredictionWidget consisting of 1 line of
     *  4 Qlabel
     */
    explicit PredictionWidget(QWidget *parent = 0);

    /*!
     * \brief change the palette of the QLabel to labelActifPalette
     * \param row: not used
     * \param column
     *
     */
    virtual void labelOn(int row, int column);

    /*!
     * \brief change the palette of the QLabel to labelInactifPalette
     * \param row: not used
     * \param column
     */
    virtual void labelOff(int row, int column);
    void setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff,
                        QColor labelOff, QColor background);

    /**
     * @brief getNumberOfLabel
     * @return the number of QLabel int this widget
     */
    virtual int getNumberOfLabels() const;

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


    /**
     * @brief the number of prediction presented by this widget
     */
    static const int NB_PREDICTION = 4;
    
signals:
    
public slots:

private:
    QHBoxLayout *predictionLayout;
    QVector<QLabel*> predictions;
    QVector<QLabel*> activePredictions;

    QPalette labelInactifPalette;
    QPalette labelActifPalette;
    QPalette backgroundPalette;
    
};

#endif // PREDICTIONWIDGET_H
