#ifndef GAME_MEMENTO_H
#define GAME_MEMENTO_H

#include "Memento.h"

class GameMemento : public Memento {
private:
	GameSave gameSave;
public:
	GameMemento(GameSave newGameSave) : gameSave(newGameSave) {};
	GameSave getState();
};

#endif