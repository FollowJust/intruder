#ifndef GAME_SAVE_H
#define GAME_SAVE_H

#include <vector>
#include <iostream>
#include <sstream>

#include "../../Exceptions/LoadException.h"
#include "../../Exceptions/SaveException.h"

class GameSave {
public:

	std::pair<int, int> playerPos;
	int playerHealth;
	int playerAmountBombs;
	int playerAmountJumps;
	bool playerCanSkipWalls;
	bool playerIsShocked;

	std::vector<std::pair<int, int>> beatEnemiesPos;
	std::vector<std::pair<int, int>> robEnemiesPos;
	std::vector<std::pair<int, int>> shockEnemiesPos;

	std::vector<std::pair<int, int>> bombsPos;
	std::vector<std::pair<int, int>> jumpsPos;
	std::vector<std::pair<int, int>> healthPos;


	int fieldWidth;
	int fieldHeight;
	std::pair<int, int> startPos;
	std::pair<int, int> finishPos;

	std::pair<int, int> datacenterPos;
	int placedDatacenters;

	int** fieldMap;

	friend std::ostream& operator<<(std::ostream& out, const GameSave& gameSave);
	friend std::stringstream& operator>>(std::stringstream& input, GameSave& gameSave);
};

#endif
