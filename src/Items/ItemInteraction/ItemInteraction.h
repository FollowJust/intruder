#ifndef ITEM_INTERACTION_H
#define ITEM_INTERACTION_H

#include "../Item.h"
#include "InteractionStrategy.h"
#include "TakeEverythingStrategy.h"

class ItemInteraction {
public:
	void setStrategy(InteractionStrategy* newStrategy);
	void setItem(Item* newItem);
	void useStrategy(Player* player);

private:
	Item* item;
	InteractionStrategy* interactionStrategy;
};


#endif