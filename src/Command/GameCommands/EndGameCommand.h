#ifndef END_GAME_COMMAND_H
#define END_GAME_COMMAND_H

#include "../Command.h"

class EndGameCommand : public Command {
public:
	EndGameCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};
#endif