#ifndef PLAYER_TURN_H
#define PLAYER_TURN_H

#include "TurnState.h"
#include "../GameManager/GameManager.h"

class PlayerTurn : public TurnState {
public:
	PlayerTurn(GameManager* gameManager) : TurnState(gameManager) {};
	void move(int deltaX, int deltaY);
	void useBombItem();
	void useJumpItem();
};

#endif