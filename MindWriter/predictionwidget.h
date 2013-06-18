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
     * \brief PredictionWidget
     * \param parent
     *  Create a PredictionWidget consisting of 1 line of
     *  4 Qlabel
     */
    explicit PredictionWidget(QWidget *parent = 0);

    /*!
     * \brief labelOn
     * \param row: not used
     * \param column
     * change the palette of the QLabel to labelActifPalette
     */
    virtual void labelOn(int row, int column);

    /*!
     * \brief labelOff
     * \param row: not used
     * \param column
     *  change the palette of the QLabel to labelInactifPalette
     */
    virtual void labelOff(int row, int column);
    void setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff,
                        QColor labelOff, QColor background);


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
