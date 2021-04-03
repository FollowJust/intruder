#ifndef START_GAME_COMMAND_H
#define START_GAME_COMMAND_H

#include "../Command.h"

class StartGameCommand : public Command {
public:
	StartGameCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};
#endif