#ifndef MEDKIT_FACTORY_H
#define MEDKIT_FACTORY_H

#include "../ItemFactory.h"
#include "MedkitItem.h"

class MedkitFactory: public ItemFactory{
public:
    Item* createItem();
};

#endif
