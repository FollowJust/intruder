#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include "Item.h"

class ItemFactory{
public:
    virtual Item* createItem() = 0;
};


#endif
