#ifndef FLASHABLE_H
#define FLASHABLE_H

class FlashableInterface
{
public:
    virtual ~FlashableInterface() {}
    virtual void labelOn(int row, int column) = 0;
    virtual void labelOff(int row, int column) = 0;
    virtual int getNumberOfLabels() const = 0;

    virtual bool oneByOneSearch() = 0;
    virtual bool binarySearch() = 0;
    virtual QVector<std::string> getActiveLabelsContent() = 0;

    virtual void allOff() = 0;
    virtual void allOn() = 0;
};

#endif // FLASHABLE_H
