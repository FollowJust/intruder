#include "MoveLeftCommand.h"

void MoveLeftCommand::execute() {
	this->gameManager->move(-1, 0);
}