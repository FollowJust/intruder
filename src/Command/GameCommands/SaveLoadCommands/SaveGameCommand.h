#ifndef SAVE_GAME_COMMAND_H
#define SAVE_GAME_COMMAND_H

#include "../../Command.h"
#include "../../../Save/Caretaker/Caretaker.h"
#include "../../../Exceptions/LoadException.h"

class SaveGameCommand : public Command {
private:
	Caretaker* caretaker;
public:
	SaveGameCommand(GameManager* gameManager, Caretaker* caretaker) : Command(gameManager) { this->caretaker = caretaker; };;
	void execute();

	void setCaretaker(Caretaker* newCaretaker) { this->caretaker = newCaretaker; };
};
#endif