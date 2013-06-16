#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStatusBar>
#include <QMenuBar>

#include "keyboardwidget.h"
#include "predictionwidget.h"

namespace defaultColorScheme
{
    static const QColor LETTER_OFF = QColor(255,255,255,130);
    static const QColor LABEL_OFF = QColor(40,40,40,200);

    static const QColor LETTER_ON = QColor(0,0,0,255);
    static const QColor LABEL_ON = QColor(255,255,255,200);

    static const QColor BACKGROUND = QColor(50,50,50,200);
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = 0);
    
signals:
    
public slots:

private:
    KeyboardWidget *keyboardW;
    PredictionWidget *predictionW;
    QTextEdit *textEdit;

    
};

#endif // MAINWINDOW_H
