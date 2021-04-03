#ifndef CARETAKER_H
#define CARETAKER_H

#include <stack>
#include <sstream>
#include "../../GameManager/GameManager.h"
#include "../Memento/Memento.h"
#include "../SaveFile/SaveFile.h"


class Caretaker {
private:
	SaveFile* saveFile;
	GameManager* gameManager;

public:
	Caretaker(GameManager* newGameManager);
	~Caretaker();

	void save();
	void undo();
};

#endif