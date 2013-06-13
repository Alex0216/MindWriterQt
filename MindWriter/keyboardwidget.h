#ifndef KEYBOARDWIDGET_H
#define KEYBOARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPalette>
#include <QTimer>

#define KEYBOARD_WIDTH 10
#define KEYBOARD_HEIGHT 4

class KeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardWidget(QWidget *parent = 0);
    void labelOn(int row, int column);
    void labelOff(int row, int column);
    
signals:
    
public slots:
    void update();

private:
    QVector<QLabel* > *keys;
    QPalette *labelInactifPalette;
    QPalette *labelActifPalette;
    QPalette *backgroundPalette;
    QTimer timer;
    int updateRow;
    int updateColumn;
    
};

#endif // KEYBOARDWIDGET_H
