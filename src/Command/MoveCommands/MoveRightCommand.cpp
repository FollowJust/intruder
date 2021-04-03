#include "MoveRightCommand.h"

void MoveRightCommand::execute() {
	this->gameManager->move(1, 0);
}