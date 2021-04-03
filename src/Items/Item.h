#ifndef ITEM_H
#define ITEM_H

#include "../Characters/Player.h"
#include <iostream>

class Item{
public:
    virtual void operator+(Player& player) = 0;
    virtual int getIndex() = 0;
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, Item const* item);
};


#endif
