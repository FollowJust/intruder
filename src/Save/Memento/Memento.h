#ifndef MEMENTO_H
#define MEMENTO_H

#include "../GameSave/GameSave.h"

class Memento {
public:
	virtual GameSave getState() = 0;
};

#endif