#ifndef INTERACTION_STRATEGY_H
#define INTERACTION_STRATEGY_H

#include "../../Characters/Player.h"
#include "../Item.h"

class InteractionStrategy {
public:
	virtual void use(Player* player, Item* item) = 0;
};

#endif