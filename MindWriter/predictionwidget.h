/*!
 * \class PredictionWidget
 * \file predictionwidget.h \version 1.1
 * \author: Alexandre St-Onge
 *
 * \brief A widget containing a group of prediction to be use
 *        with the KeyboardWidget
 *
 * Each label has a minimum width of 50 and a maximum
 * height of 50.
 * Optimaly, the widget should only have one (1) row
 */
#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "flashablewidget.h"

class PredictionWidget :public FlashableWidget
{
public:
    /*!
     * \brief Create a PredictionWidget
     * \param width the number of column the widget will have
     * \param height the number of row the widget will have
     * \param parent
     */
    explicit PredictionWidget(int width, int height, QWidget *parent = 0);
    
signals:
    
public slots:

private:
};

#endif // PREDICTIONWIDGET_H
