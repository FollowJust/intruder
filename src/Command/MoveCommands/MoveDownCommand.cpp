#include "MoveDownCommand.h"

void MoveDownCommand::execute() {
	this->gameManager->move(0, 1);
}