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

    static const int NB_PREDICTION = 4;
    
signals:
    
public slots:

private:
    QHBoxLayout *predictionLayout;
    QVector<QLabel*> predictions;
    
};

#endif // PREDICTIONWIDGET_H
