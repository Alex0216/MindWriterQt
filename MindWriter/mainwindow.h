/**
 * \file mainwindow.h \version 1.0
 * \class MainWindow
 * \author: Alexandre St-Onge, Julien Aymong
 *
 * \brief A window containing two flashable widget,
 * one KeyboardWidget and one PredictionWidget, and
 * a QTextEdit to print the choosen letter/word.
 *
 * The three widgets are in a QVBoxLayout with the
 * QTextEdit on top, followed by the PredictionWidget
 * and the KeyboardWidget at the bottom
 *
 * © TheBCIProject
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QPair>
#include <QVector>
#include <QKeyEvent>


#include "keyboardwidget.h"
#include "predictionwidget.h"
#include "keyboardselectionwidget.h"

/**
 * \brief The default color scheme for the program
 */
namespace defaultColorScheme
{
    /**
     * @brief letter when not active: Gray
     */
    static const QColor LETTER_OFF = QColor(255,255,255,130);
    /**
     * @brief label's background when inactive: Black
     */
    static const QColor LABEL_OFF = QColor(40,40,40,200);

    /**
     * @brief letter's color when active: Black
     */
    static const QColor LETTER_ON = QColor(0,0,0,255);

    /**
     * @brief label's background when active: White
     */
    static const QColor LABEL_ON = QColor(255,255,255,200);

    /**
     * @brief Bbackground color: Black
     */
    static const QColor BACKGROUND = QColor(50,50,50,200);
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QMainWindow *parent = 0);

    /**
     * @brief the delay between each flash
     */
    static const int DELAY = 300;

    enum FlashMode {
        OneByOne, /**< Flash one label after the other. */
        BinarySearch /**< Flash one row/column after the other. */
    };

    /**
     * @brief called by the updateFlash slot. \n
     *  This mode flashes the labels of PredictionWidget and
     *  KeyboardWidget one after the others according to the order
     *  specified. By default it goes in ordger.
     */
    void oneByOneSearch();

    /**
      * @brief called by the updateFlash slot. \n
      * This mode implement a binary search like algorythm
      * by flashing half the KeyboardWidget. On it know in wich
      * halve the label it repeat the procedure with the smaller
      * keyboard portion until the label is found
      */
    void binarySearch();

    void keyPressEvent(QKeyEvent *event);
    
signals:
    
public slots:

    /**
     * @brief update the KeyboardWidget and PredictionWidget
     * according to the present configuration. \n
     * Called when timer_ reach DELAY
     */
    void updateFlash();

private:
    void createActions();

    KeyboardWidget *keyboardW;
    PredictionWidget *predictionW;
    QTextEdit *textEdit;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *settingMenu;
    QMenu *keyboardMenu;
    QMenu *flashMenu_;
    QAction *qwertyAct;
    QAction *azertyAct;
    QAction *oneByOneAct;
    QAction *binarySearchAct;
    QAction *selectFlashAct;

    QTimer timer_; ///< Timer use to control the label. Details.
    FlashableWidget* currentWidget_;

    bool debouncer_;
    FlashMode flashMode_;
    int flashIndex_;


private slots:
    void selectQWERTYKeyboardLayout();
    void selectAZERTYKeyboardLayout();
    void selectOneByOneFlashOption();
    void selectBinarySearchFlashOption();
    
};

#endif // MAINWINDOW_H
