#include "MoveUpCommand.h"

void MoveUpCommand::execute() {
	this->gameManager->move(0, -1);
}