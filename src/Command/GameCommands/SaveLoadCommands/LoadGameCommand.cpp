#include "LoadGameCommand.h"

void LoadGameCommand::execute() {
	caretaker->undo();
}