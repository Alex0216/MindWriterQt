#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QTimer>


class KeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = 0);
    void labelOn(int row, int column);
    void labelOff(int row, int column);
    void setColorScheme(QColor letterOn, QColor labelOn, QColor letterOff,
                        QColor labelOff, QColor background);


    static const int KEYBOARD_WIDTH = 10;
    static const int KEYBOARD_HEIGHT = 4;
    static const int DELAY = 300;

signals:
    
public slots:
    void update();

private:
    QVector<QLabel* > keys;
    QPalette labelInactifPalette;
    QPalette labelActifPalette;
    QPalette backgroundPalette;
    QTimer timer;
    int updateRow;
    int updateColumn;
    
};

#endif // KEYBOARDWIDGET_H
