#ifndef COMMAND_H
#define COMMAND_H

#include "../GameManager/GameManager.h"

class Command {
protected:
	GameManager* gameManager;
public:
	Command(GameManager* gameManager) { this->gameManager = gameManager; };
	virtual void execute() = 0;
};

#endif