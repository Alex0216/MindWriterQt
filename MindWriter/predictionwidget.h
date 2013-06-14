#ifndef PREDICTIONWIDGET_H
#define PREDICTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

#define NB_PREDICTION 4

class PredictionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PredictionWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    QHBoxLayout *predictionLayout;
    QVector<QLabel*> predictions;
    
};

#endif // PREDICTIONWIDGET_H
