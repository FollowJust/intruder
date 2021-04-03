#include "MedkitFactory.h"


Item* MedkitFactory::createItem(){
    return new MedkitItem;
}
