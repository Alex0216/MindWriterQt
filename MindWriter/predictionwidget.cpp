#include "predictionwidget.h"

#include <iostream>

using namespace std;

PredictionWidget::PredictionWidget(QWidget *parent) :
    QWidget(parent)
{
    predictionLayout = new QHBoxLayout();
    predictions = QVector<QLabel*>();

    QFont f("Helvetica", 20);

    for (int i = 0; i< NB_PREDICTION; ++i)
    {
        QLabel *labelPrediction = new QLabel("test");
        labelPrediction->setFont(f);
        labelPrediction->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        labelPrediction->setMinimumWidth(50);
        labelPrediction->setMaximumHeight(50);
        labelPrediction->setScaledContents(true);
        labelPrediction->setFrameShape(QFrame::Box);
        labelPrediction->setLineWidth(3);
        labelPrediction->setAlignment(Qt::AlignCenter);
        labelPrediction->setPalette(labelInactifPalette);
        labelPrediction->setAutoFillBackground(true);
        predictionLayout->addWidget(labelPrediction);
        predictions.push_back(labelPrediction);
    }

    setLayout(predictionLayout);

}

void PredictionWidget::labelOn(int, int column)
{
   //row is always 0
    if(column < 4)
        predictions.at(column)->setPalette(labelActifPalette);
}

void PredictionWidget::labelOff(int, int column)
{
    //row is always 0
     if(column < 4)
         predictions.at(column)->setPalette(labelInactifPalette);
}

void PredictionWidget::setColorScheme(QColor letterOn, QColor labelOn,
                   QColor letterOff, QColor labelOff, QColor background)
{
    /*
     *Palette pour les label Inactifs
     * Texte blanc/gris et fond noir-ish
     */

    //Texte blanc
    QBrush brushInactif1;
    brushInactif1.setColor(letterOff);
    brushInactif1.setStyle(Qt::SolidPattern);

    //Background noir
    QBrush brushInactif2;
    brushInactif2.setColor(labelOff);
    brushInactif2.setStyle(Qt::SolidPattern);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushInactif1);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushInactif1);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::Window, brushInactif2);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushInactif2);

    /*
     *Palette pour les label Actifs
     * Texte noir et fond blanc
     */
    //Texte noir
    QBrush brushActif1;
    brushActif1.setColor(letterOn);
    brushActif1.setStyle(Qt::SolidPattern);

    //Background Blanc
    QBrush brushActif2;
    brushActif2.setColor(QColor(labelOn));
    brushActif2.setStyle(Qt::SolidPattern);

    labelActifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushActif1);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushActif1);

    labelActifPalette.setBrush(QPalette::Active, QPalette::Window, brushActif2);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushActif2);

    /*
     *Palette pour le background
     *noir-ish
     */
    QBrush brushBack1(background);
    QBrush brushBack2(background);

    backgroundPalette.setBrush(QPalette::Active, QPalette::Window, brushBack1);
    backgroundPalette.setBrush(QPalette::Inactive, QPalette::Window, brushBack2);

    //----------------------------------------------------------------------

    setPalette(backgroundPalette);
    setAutoFillBackground(true);

    for(int i = 0; i < predictions.size(); ++i)
        predictions.at(i)->setPalette(labelInactifPalette);

}

int PredictionWidget::getNumberOfLabels() const
{
    return predictions.size();
}

bool PredictionWidget::oneByOneSearch()
{
    static int index = 0;
    QLabel* lastLabel;
    if (index == 0)
    {
       lastLabel = predictions.last();
    }
    else
    {
        lastLabel = predictions.at(index-1);
    }

    lastLabel->setPalette(labelInactifPalette);
    if (activePredictions.contains(lastLabel))
        activePredictions.remove(activePredictions.indexOf(lastLabel));
    if( index != predictions.size())
    {
        activePredictions.push_back(predictions.at(index));
        predictions.at(index++)->setPalette(labelActifPalette);
        return false;
    }
    else
    {
        index = 0;
        return true;
    }

    return false;

}

bool PredictionWidget::binarySearch()
{
    //If empty: state 1
    if (vSelectedHalve_.isEmpty())
    {
        vSelectedHalve_ = predictions;
    }

    if (vFirstHalve_.isEmpty() && vSecondHalve_.isEmpty())
    {
        //Turn the right side on
        //index%NB_PREDICTION correspond to the column
        // so the right side is when that number < NB_PREDICTION/2

        int half = vSelectedHalve_.size() / 2;
        for(int i = 0; i < vSelectedHalve_.size(); ++i)
        {
            int index = i % vSelectedHalve_.size();
            if( index < half)
                vFirstHalve_.push_back(vSelectedHalve_.at(index));
            else
                vSecondHalve_.push_back(vSelectedHalve_.at(index));
        }
    }
    static int alternate = 1;
    //alternate between the two vector
    if(alternate > 0)
    {
        currentHalve = 1;
        for_each(vFirstHalve_.begin(), vFirstHalve_.end(), [this] (QLabel* l){
                     l->setPalette(labelActifPalette);
                 });
        for_each(vSecondHalve_.begin(), vSecondHalve_.end(), [this] (QLabel* l){
            l->setPalette(labelInactifPalette);
        });
    }
    else
    {
        currentHalve = 2;
        for_each(vFirstHalve_.begin(), vFirstHalve_.end(), [this] (QLabel* l){
                     l->setPalette(labelInactifPalette);
                 });
        for_each(vSecondHalve_.begin(), vSecondHalve_.end(), [this] (QLabel* l){
            l->setPalette(labelActifPalette);
        });
    }
    alternate *= -1;


    return false;
}

QVector<QString> PredictionWidget::getActiveLabelsContent()
{
    QVector<QString> contents;
    for_each(activePredictions.begin(),activePredictions.end(), [&contents] (QLabel* l){
        contents.push_back(l->text());
    } );
    return contents;

}

bool PredictionWidget::selectHalve()
{
    if( currentHalve == 1)
        vSelectedHalve_ = vFirstHalve_;
    else
        vSelectedHalve_ = vSecondHalve_;

    vFirstHalve_.clear();
    vSecondHalve_.clear();
    activePredictions = vSelectedHalve_;

    if( vSelectedHalve_.size() == 1)
    {
        vSelectedHalve_.clear();
        return true;
    }
    return false;
}

void PredictionWidget::allOff()
{
    for (int i = 0; i < predictions.size(); ++i)
    {
        predictions.at(i)->setPalette(labelInactifPalette);
    }
    activePredictions.clear();
}

void PredictionWidget::allOn()
{
    for (int i = 0; i < predictions.size(); ++i)
    {
        QLabel* label = predictions.at(i);
        if(!activePredictions.contains(label))
        {
            label->setPalette(labelActifPalette);
            activePredictions.push_back(label);
        }
    }

}
