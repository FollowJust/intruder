#ifndef ENEMY_TURN_H
#define ENEMY_TURN_H

#include "TurnState.h"
#include "../GameManager/GameManager.h"

class EnemyTurn : public TurnState {
public:
	EnemyTurn(GameManager* gameManager) : TurnState(gameManager) {};
	void move(int deltaX, int deltaY);
	void useBombItem();
	void useJumpItem();
};

#endif