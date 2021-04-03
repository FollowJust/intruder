#ifndef BOMB_COMMAND_H
#define BOMB_COMMAND_H

#include "../Command.h"

class BombCommand : public Command {
public:
	BombCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};
#endif