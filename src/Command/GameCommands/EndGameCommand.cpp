#include "EndGameCommand.h"

void EndGameCommand::execute() {
	this->gameManager->endGame();
}