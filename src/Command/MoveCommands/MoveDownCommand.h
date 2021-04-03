#ifndef MOVE_DOWN_COMMAND_H
#define MOVE_DOWN_COMMAND_H

#include "../Command.h"
class MoveDownCommand : public Command {
public:
	MoveDownCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};

#endif
