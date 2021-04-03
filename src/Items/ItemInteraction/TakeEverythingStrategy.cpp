#include "TakeEverythingStrategy.h"

void TakeEverythingStrategy::use(Player* player, Item* item) {
	*item + *player;
}