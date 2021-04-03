#include "StartGameCommand.h"

void StartGameCommand::execute() {
	this->gameManager->startGame();
}