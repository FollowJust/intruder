#include "ItemInteraction.h"

void ItemInteraction::setItem(Item* newItem) {
	this->item = newItem;
}

void ItemInteraction::setStrategy(InteractionStrategy* newStrategy) {
	this->interactionStrategy = newStrategy;
}
void ItemInteraction::useStrategy(Player* player) {
	if (!item) {
		throw std::invalid_argument("Item is not assigned");
	}
	interactionStrategy->use(player, item);
}