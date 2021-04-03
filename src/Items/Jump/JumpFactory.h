#ifndef JUMP_FACTORY_H
#define JUMP_FACTORY_H

#include "../ItemFactory.h"
#include "JumpItem.h"

class JumpFactory : public ItemFactory{
public:
    Item* createItem();
};

#endif
