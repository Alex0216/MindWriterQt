#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "flashable.h"

class PredictionWidget :public Flashable
{
public:
    /*!
     * \brief Create a PredictionWidget consisting of 1 line of
     *  4 Qlabel
     * \param parent
     *  Create a PredictionWidget consisting of 1 line of
     *  4 Qlabel
     */
    explicit PredictionWidget(int row, int column, QWidget *parent = 0);
    
signals:
    
public slots:

private:
};

#endif // PREDICTIONWIDGET_H
