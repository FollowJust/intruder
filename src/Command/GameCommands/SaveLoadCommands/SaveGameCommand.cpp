#include "SaveGameCommand.h"

void SaveGameCommand::execute() {
	caretaker->save();
}