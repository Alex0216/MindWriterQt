#ifndef FLASHABLE_H
#define FLASHABLE_H

class Flashable
{
public:
    virtual ~Flashable() {};
    virtual void labelOn(int row, int column) = 0;
    virtual void labelOff(int row, int column) = 0;
};

#endif // FLASHABLE_H
