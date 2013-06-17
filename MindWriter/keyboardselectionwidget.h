#ifndef KEYBOARDSELECTIONWIDGET_H
#define KEYBOARDSELECTIONWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

class KeyboardSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeyboardSelectionWidget(QWidget *parent = 0);
    QString getChoice();

signals:

public slots:
    void mainWindow();

private:
    QVBoxLayout *frameSelection;
    QComboBox *keyboardLayoutSelection;
    QGroupBox *keyboardGroup;

    QHBoxLayout *buttons;
    QPushButton *select;
    QPushButton *quit;
    QVBoxLayout *mainLayout;

    QString choice;
};

#endif // KEYBOARDSELECTIONWIDGET_H
