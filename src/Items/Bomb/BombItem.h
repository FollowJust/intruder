#ifndef BOMB_ITEM_H
#define BOMB_ITEM_H

#include "../Item.h"

class BombItem: public Item{
public:
    void operator+(Player& player);
    int getIndex() { return 2; };
    void print(std::ostream& out) const;
};

#endif
