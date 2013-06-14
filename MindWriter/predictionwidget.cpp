#include "predictionwidget.h"

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
        predictionLayout->addWidget(labelPrediction);
        predictions.push_back(labelPrediction);
    }

    setLayout(predictionLayout);

}
