#include "BeatPolicy.h"

void BeatPolicy::operator+(Player* player) {
	player->takeDamage(1);
}