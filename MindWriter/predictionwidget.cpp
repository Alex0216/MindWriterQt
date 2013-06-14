#include "predictionwidget.h"

PredictionWidget::PredictionWidget(QWidget *parent) :
    QWidget(parent)
{
    predictionLayout = new QHBoxLayout();
    predictions = QVector<QLabel*>();

    /*
     *Palette pour les label Inactifs
     * Texte blanc/gris et fond noir-ish
     */
   QPalette labelInactifPalette = QPalette();
    //Texte blanc
    QBrush brushInactif1;
    brushInactif1.setColor(QColor(255,255,255,130));
    brushInactif1.setStyle(Qt::SolidPattern);

    //Background noir
    QBrush brushInactif2;
    brushInactif2.setColor(QColor(40,40,40,200));
    brushInactif2.setStyle(Qt::SolidPattern);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushInactif1);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushInactif1);

    labelInactifPalette.setBrush(QPalette::Active, QPalette::Window, brushInactif2);
    labelInactifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushInactif2);

    /*
     *Palette pour les label Actifs
     * Texte noir et fond blanc
     */
    QPalette labelActifPalette = QPalette();
    //Texte noir
    QBrush brushActif1;
    brushActif1.setColor(QColor(0,0,0,255));
    brushActif1.setStyle(Qt::SolidPattern);

    //Background Blanc
    QBrush brushActif2;
    brushActif2.setColor(QColor(255,255,255,200));
    brushActif2.setStyle(Qt::SolidPattern);

    labelActifPalette.setBrush(QPalette::Active, QPalette::WindowText, brushActif1);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushActif1);

    labelActifPalette.setBrush(QPalette::Active, QPalette::Window, brushActif2);
    labelActifPalette.setBrush(QPalette::Inactive, QPalette::Window, brushActif2);

    QPalette backgroundPalette = QPalette();

    QBrush brushBack1(QColor(50,50,50,200));
    QBrush brushBack2(QColor(10,10,10,255));

    backgroundPalette.setBrush(QPalette::Active, QPalette::Window, brushBack1);
    backgroundPalette.setBrush(QPalette::Inactive, QPalette::Window, brushBack2);

    //----------------------------------------------------------------------

    setPalette(backgroundPalette);
    setAutoFillBackground(true);

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
