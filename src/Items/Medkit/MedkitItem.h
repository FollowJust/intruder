#ifndef MEDKIT_ITEM_H
#define MEDKIT_ITEM_H

#include "../Item.h"

class MedkitItem: public Item{
public:
    void operator+(Player& player);
    int getIndex() { return 0; };
    void print(std::ostream& out) const;
};

#endif
