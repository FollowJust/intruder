#include "JumpCommand.h"

void JumpCommand::execute() {
	this->gameManager->useJumpItem();
}