#ifndef BOMB_FACTORY_H
#define BOMB_FACTORY_H

#include "../ItemFactory.h"
#include "BombItem.h"

class BombFactory: public ItemFactory{
public:
    Item* createItem();
};

#endif
