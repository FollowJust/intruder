#ifndef JUMP_ITEM_H
#define JUMP_ITEM_H

#include "../Item.h"

class JumpItem : public Item{
public:
    void operator+(Player& player);
    int getIndex() { return 1; };
    void print(std::ostream& out) const;
};

#endif
