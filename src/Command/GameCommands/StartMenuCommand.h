#ifndef START_MENU_COMMAND_H
#define START_MENU_COMMAND_H

#include "../Command.h"

class StartMenuCommand : public Command {
public:
	StartMenuCommand(GameManager* gameManager) : Command(gameManager) {};
	void execute();
};
#endif