/**
 * flashablewidget.cpp \version 1.1
 * \author Alexandre St-Onge
 * \brief Implementation of the Flashable class
 *
 */

#include "flashablewidget.h"

FlashableWidget::FlashableWidget(int width, int height, QWidget *parent):
    QWidget(parent) ,vLabels_(), width_(width), height_(height),
    vActiveLabels_(), inactiveLabelPalette(), activeLabelPalette(),
    backgroundPalette(), currentHalve(0), selectedHalveWidth(0),
    selectedHalveHeight(0), firstHalveWidth(0), firstHalveHeight(0),
    secondHalveWidth(0), secondHalveHeight(0)
{
    grid = new QGridLayout;

    QFont f("Helvetica", 20);
    for(int row = 0; row < height_; ++row)
    {
        for(int column = 0; column < width_; ++column)
        {
            QLabel *label = new QLabel();
            label->setFont(f);
            label->setScaledContents(true);
            label->setFrameShape(QFrame::Box);
            label->setLineWidth(3);
            label->setAlignment(Qt::AlignCenter);
            label->setPalette(inactiveLabelPalette);
            label->setAutoFillBackground(true);
            grid->addWidget(label, row, column);
            vLabels_.push_back(label);
        }
    }

    setLayout(grid);
}

void FlashableWidget::setColorScheme(QColor letterOn, QColor labelOn,
                  QColor letterOff, QColor labelOff, QColor background)
{
    /**
     * Palette pour les label Inactifs
     */
    QBrush brushInactif1;
    brushInactif1.setColor(letterOff);
    brushInactif1.setStyle(Qt::SolidPattern);

    QBrush brushInactif2;
    brushInactif2.setColor(labelOff);
    brushInactif2.setStyle(Qt::SolidPattern);

    inactiveLabelPalette.setBrush(QPalette::Active, QPalette::WindowText, brushInactif1);
    inactiveLabelPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushInactif1);

    inactiveLabelPalette.setBrush(QPalette::Active, QPalette::Window, brushInactif2);
    inactiveLabelPalette.setBrush(QPalette::Inactive, QPalette::Window, brushInactif2);

    /**
     *  Palette pour les label Actifs
     */
    QBrush brushActif1;
    brushActif1.setColor(letterOn);
    brushActif1.setStyle(Qt::SolidPattern);

    QBrush brushActif2;
    brushActif2.setColor(QColor(labelOn));
    brushActif2.setStyle(Qt::SolidPattern);

    activeLabelPalette.setBrush(QPalette::Active, QPalette::WindowText, brushActif1);
    activeLabelPalette.setBrush(QPalette::Inactive, QPalette::WindowText, brushActif1);

    activeLabelPalette.setBrush(QPalette::Active, QPalette::Window, brushActif2);
    activeLabelPalette.setBrush(QPalette::Inactive, QPalette::Window, brushActif2);

    /**
     * Palette pour le background
     */
    QBrush brushBack1(background);
    QBrush brushBack2(background);

    backgroundPalette.setBrush(QPalette::Active, QPalette::Window, brushBack1);
    backgroundPalette.setBrush(QPalette::Inactive, QPalette::Window, brushBack2);

    //----------------------------------------------------------------------

    setPalette(backgroundPalette);
    setAutoFillBackground(true);

    for (int i = 0; i < vLabels_.size(); ++i )
    {
        vLabels_.at(i)->setPalette(inactiveLabelPalette);
    }

}

void FlashableWidget::labelOn(int row, int column)
{
    int index = column + row*width_;
    QLabel* label = vLabels_.at(index);
    label->setPalette(activeLabelPalette);
    vActiveLabels_.push_back(label);
}

void FlashableWidget::labelOff(int row, int column)
{
    int index = column + row*width_;
    QLabel* label = vLabels_.at(index);
    label->setPalette(inactiveLabelPalette);
    vActiveLabels_.remove(vActiveLabels_.indexOf(label));
}

int FlashableWidget::getNumberOfLabels() const
{
    return vLabels_.size();
}

bool FlashableWidget::oneByOneSearch()
{
    static int index = 0;

    QLabel* lastLabel;
    if(index == 0)
        lastLabel = vLabels_.last();
    else
        lastLabel = vLabels_.at(index-1);

    lastLabel->setPalette(inactiveLabelPalette);
    if(vActiveLabels_.contains(lastLabel))
        vActiveLabels_.remove(vActiveLabels_.indexOf(lastLabel));

    if( index != vLabels_.size())
    {
        vActiveLabels_.push_back(vLabels_.at(index));
        vLabels_.at(index++)->setPalette(activeLabelPalette);
    }
    else
    {
        index = 0;
        return true;
    }

    return false;
}

bool FlashableWidget::binarySearch()
{
    if(vSelectedHalve_.isEmpty())
    {
        vSelectedHalve_ = vLabels_;
        selectedHalveWidth = width_;
        selectedHalveHeight = height_;
    }

    if(vFirstHalve_.isEmpty() && vSecondHalve_.isEmpty())
    {
        //Divide the grid according to the longuest side
        if(selectedHalveWidth > selectedHalveHeight)
        {
            for(int i = 0; i < vSelectedHalve_.size(); ++i)
            {
                int index = i % selectedHalveWidth;
                if( index < selectedHalveWidth/2)
                    vFirstHalve_.push_back(vSelectedHalve_.at(i));
                else
                    vSecondHalve_.push_back(vSelectedHalve_.at(i));
            }
            //height stays the same
            firstHalveHeight = selectedHalveHeight;
            secondHalveHeight = selectedHalveHeight;

            firstHalveWidth = selectedHalveWidth/2;
            secondHalveWidth = selectedHalveWidth - firstHalveWidth;
        }
        else
        {
            int separation = vSelectedHalve_.size()/2;

            //To have complete row only
            separation = separation - separation%selectedHalveWidth;
            for(int i = 0; i < vSelectedHalve_.size(); ++i)
            {
                if( i < separation)
                    vFirstHalve_.push_back(vSelectedHalve_.at(i));
                else
                    vSecondHalve_.push_back(vSelectedHalve_.at(i));
            }

            //width stays the same
            firstHalveWidth = selectedHalveWidth;
            secondHalveWidth = selectedHalveWidth;

            firstHalveHeight = selectedHalveHeight/2;
            secondHalveHeight = selectedHalveHeight = firstHalveHeight;

        }
    }

    ///The two side will flash in alternance each time the method is called
    static int alternate = 1;
    if(alternate > 0)
    {
        currentHalve = 1;
        std::for_each(vFirstHalve_.begin(), vFirstHalve_.end(), [this] (QLabel* l){
                     l->setPalette(activeLabelPalette);
                 });
        std::for_each(vSecondHalve_.begin(), vSecondHalve_.end(), [this] (QLabel* l){
            l->setPalette(inactiveLabelPalette);
        });
    }
    else
    {
        currentHalve = 2;
        std::for_each(vFirstHalve_.begin(), vFirstHalve_.end(), [this] (QLabel* l){
                     l->setPalette(inactiveLabelPalette);
                 });
        std::for_each(vSecondHalve_.begin(), vSecondHalve_.end(), [this] (QLabel* l){
            l->setPalette(activeLabelPalette);
        });
    }
    alternate *= -1;

    return false;

}

QVector<QString> FlashableWidget::getActiveLabelsContent() const
{
    QVector<QString> contents;
    std::for_each(vActiveLabels_.begin(),vActiveLabels_.end(), [&contents] (QLabel* l){
        contents.push_back(l->text());
    } );
    return contents;
}

bool FlashableWidget::selectHalve()
{
    if( currentHalve == 1)
    {
        vSelectedHalve_ = vFirstHalve_;
        selectedHalveHeight = firstHalveHeight;
        selectedHalveWidth = firstHalveWidth;
    }
    else
    {
        vSelectedHalve_ = vSecondHalve_;
        selectedHalveHeight = secondHalveHeight;
        selectedHalveWidth = secondHalveWidth;
    }

    vFirstHalve_.clear();
    vSecondHalve_.clear();
    vActiveLabels_ = vSelectedHalve_;

    if( vSelectedHalve_.size() == 1)
    {
        vSelectedHalve_.clear();
        return true;
    }
    return false;

}

void FlashableWidget::allOff()
{
    for (int i = 0; i < vLabels_.size(); ++i)
    {
        vLabels_.at(i)->setPalette(inactiveLabelPalette);
    }
    vActiveLabels_.clear();
}

void FlashableWidget::allOn()
{
    for (int i = 0; i < vLabels_.size(); ++i)
    {
        QLabel* label = vLabels_.at(i);
        if(!vActiveLabels_.contains(label))
        {
            label->setPalette(inactiveLabelPalette);
            vActiveLabels_.push_back(label);
        }
    }
}



