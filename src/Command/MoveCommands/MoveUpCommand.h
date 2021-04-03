#ifndef MOVE_UP_COMMAND_H
#define MOVE_UP_COMMAND_H

#include "../Command.h"
class MoveUpCommand : public Command {
public:
	MoveUpCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};

#endif
