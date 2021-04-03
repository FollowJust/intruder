#include "RobPolicy.h"

void RobPolicy::operator+(Player* player) {
	player->removeBombs();
	player->removeJump();
}