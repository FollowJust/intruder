#ifndef JUMP_COMMAND_H
#define JUMP_COMMAND_H

#include "../Command.h"

class JumpCommand : public Command {
public:
	JumpCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};
#endif