#include "Caretaker.h"

Caretaker::Caretaker(GameManager* newGameManager) {
	gameManager = newGameManager;
	saveFile = new SaveFile("save.txt");
}

void Caretaker::save() {
	try {
		Memento* newSave = gameManager->saveGame();
		std::ostringstream tmp;
		tmp << newSave->getState();

		saveFile->write(tmp.str().c_str());
	}
	catch (const FileException& e) {
		std::cerr << e.what();
		return;
	}
	catch (const SaveException& e) {
		std::cerr << e.what();
		return;
	}
}

void Caretaker::undo() {

	try {
		std::stringstream saveText = saveFile->read();

		GameSave gameSaveText;
		saveText >> gameSaveText;

		Memento* test = new GameMemento(gameSaveText);

		gameManager->loadGame(test);
	}
	catch (const FileException& e) {
		std::cerr << e.what();
	}
	catch (const LoadException& e) {
		std::cerr << e.what();
	}
}


Caretaker::~Caretaker() {
	if (saveFile)
		delete saveFile;
}