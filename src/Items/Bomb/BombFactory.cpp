#include "BombFactory.h"


Item* BombFactory::createItem(){
    return new BombItem;
}
