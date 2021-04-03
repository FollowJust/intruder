#include "BombCommand.h"

void BombCommand::execute() {
	this->gameManager->useBombItem();
}