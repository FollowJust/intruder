#ifndef MOVE_RIGHT_COMMAND_H
#define MOVE_RIGHT_COMMAND_H

#include "../Command.h"
class MoveRightCommand : public Command {
public:
	MoveRightCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};

#endif
