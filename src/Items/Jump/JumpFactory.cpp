#include "JumpFactory.h"


Item* JumpFactory::createItem(){
    return new JumpItem;
}
