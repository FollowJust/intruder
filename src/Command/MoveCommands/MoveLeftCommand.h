#ifndef MOVE_LEFT_COMMAND_H
#define MOVE_LEFT_COMMAND_H

#include "../Command.h"
class MoveLeftCommand : public Command {
public:
	MoveLeftCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};

#endif
