#include "PlayerTurn.h"


void PlayerTurn::move(int deltaX, int deltaY) {
	gameManager->movePlayer(deltaX, deltaY);
}


void PlayerTurn::useBombItem() {
	gameManager->playerUseBombItem();
}

void PlayerTurn::useJumpItem() {
	gameManager->playerUseJumpItem();
}