#ifndef LOAD_GAME_COMMAND_H
#define LOAD_GAME_COMMAND_H

#include "../../Command.h"
#include "../../../Save/Caretaker/Caretaker.h"
#include "../../../Exceptions/LoadException.h"

class LoadGameCommand : public Command {
private:
	Caretaker* caretaker;
public:
	LoadGameCommand(GameManager* gameManager, Caretaker* caretaker) : Command(gameManager) { this->caretaker = caretaker; };
	void execute();

	void setCaretaker(Caretaker* newCaretaker) { this->caretaker = newCaretaker; };
};
#endif