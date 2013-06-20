/**
 * \file predictionwidget.cpp \version 1.1
 * \author Alexandre St-Onge
 *
 * \brief Implementation of the PredictionWidget class
 */

#include "predictionwidget.h"

using namespace std;

PredictionWidget::PredictionWidget(int width, int height, QWidget *parent) :
    FlashableWidget(width, height, parent)
{
    for (int i = 0; i< vLabels_.size(); ++i)
    {
        QLabel *labelPrediction = vLabels_.at(i);
        labelPrediction->setText("Salut");
        labelPrediction->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        labelPrediction->setMinimumWidth(50);
        labelPrediction->setMaximumHeight(50);
    }
}


