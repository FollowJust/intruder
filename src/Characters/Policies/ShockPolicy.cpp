#include "ShockPolicy.h"

void ShockPolicy::operator+(Player* player) {
	player->setIsShocked(true);
}