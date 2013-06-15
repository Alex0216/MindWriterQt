#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


class PredictionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PredictionWidget(QWidget *parent = 0);

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
