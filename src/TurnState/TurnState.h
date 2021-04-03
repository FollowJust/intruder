#ifndef TURN_STATE_H
#define TURN_STATE_H

#include "../Characters/Enemy.h"
#include "..\Characters\Policies\Policy.h"
#include "..\Characters\Policies\BeatPolicy.h"
#include "..\Characters\Policies\RobPolicy.h"
#include "..\Characters\Policies\ShockPolicy.h"



class GameManager;

class TurnState {
protected:
	GameManager* gameManager;

public:
	TurnState(GameManager* gameManager) { this->gameManager = gameManager; };

	virtual void move(int deltaX, int deltaY) = 0;
	virtual void useBombItem() = 0;
	virtual void useJumpItem() = 0;


};

#endif