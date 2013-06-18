#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "flashable.h"

class PredictionWidget : public QWidget, public Flashable
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
     * @brief the number of prediction presented by this widget
     */
    static const int NB_PREDICTION = 4;
    
signals:
    
public slots:

private:
    QHBoxLayout *predictionLayout;
    QVector<QLabel*> predictions;

    QPalette labelInactifPalette;
    QPalette labelActifPalette;
    QPalette backgroundPalette;
    
};

#endif // PREDICTIONWIDGET_H
