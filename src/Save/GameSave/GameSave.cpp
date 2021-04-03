#include "GameSave.h"

std::ostream& operator<< (std::ostream& out, const GameSave& gameSave) {

	out << gameSave.fieldWidth << " " << gameSave.fieldHeight << "\n";

    out << gameSave.playerPos.first << " " << gameSave.playerPos.second << "\n";
	out << gameSave.playerHealth << " " << gameSave.playerAmountBombs << " " << gameSave.playerAmountJumps << "\n";
	out << gameSave.playerCanSkipWalls << " " << gameSave.playerIsShocked << "\n";

	out << gameSave.beatEnemiesPos.size() << "\n";
	for (auto position : gameSave.beatEnemiesPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.robEnemiesPos.size() << "\n";
	for (auto position : gameSave.robEnemiesPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.shockEnemiesPos.size() << "\n";
	for (auto position : gameSave.shockEnemiesPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.bombsPos.size() << "\n";
	for (auto position : gameSave.bombsPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.jumpsPos.size() << "\n";
	for (auto position : gameSave.jumpsPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.healthPos.size() << "\n";
	for (auto position : gameSave.healthPos) {
		out << position.first << " " << position.second << "\n";
	}

	out << gameSave.startPos.first << " " << gameSave.startPos.second << "\n";
	out << gameSave.finishPos.first << " " << gameSave.finishPos.second << "\n";

	out << gameSave.placedDatacenters << "\n";
	out << gameSave.datacenterPos.first << " " << gameSave.datacenterPos.second << "\n";

	for (int y = 0; y < gameSave.fieldHeight; y++) {
		for (int x = 0; x < gameSave.fieldWidth; x++) {
			out << gameSave.fieldMap[y][x] << " ";
		}
		out << "\n";
	}

    return out;
}

std::stringstream& operator>> (std::stringstream& input, GameSave& gameSave) {
	int vectorSize, x, y;

	input >> gameSave.fieldWidth >> gameSave.fieldHeight;

	input >> gameSave.playerPos.first >> gameSave.playerPos.second;
	if (gameSave.playerPos.first > gameSave.fieldWidth || gameSave.playerPos.first < 0 || gameSave.playerPos.second > gameSave.fieldHeight || gameSave.playerPos.second < 0) {
		throw LoadException("PlayerPos is corrupted.\n");
	}
	input >> gameSave.playerHealth >> gameSave.playerAmountBombs >> gameSave.playerAmountJumps;
	if (gameSave.playerHealth < 0 || gameSave.playerAmountBombs < 0 || gameSave.playerAmountJumps < 0) {
		throw LoadException("PlayerStats are corrupted.\n");
	}
	input >> gameSave.playerCanSkipWalls >> gameSave.playerIsShocked;
	if ((gameSave.playerCanSkipWalls < 0 || gameSave.playerCanSkipWalls > 1) || (gameSave.playerIsShocked < 0 || gameSave.playerIsShocked > 1)) {
		throw LoadException("PlayerStats are corrupted.\n");
	}

	input >> vectorSize;
	gameSave.beatEnemiesPos.clear();
	for (int i = 0; i < vectorSize; i++) {
		
		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("BeatEnemyPos is corrupted.\n");
		}
		gameSave.beatEnemiesPos.push_back(std::make_pair(x, y));
	}

	input >> vectorSize;
	gameSave.robEnemiesPos.clear();
	for (int i = 0; i < vectorSize; i++) {

		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("RobEnemyPos is corrupted.\n");
		}
		gameSave.robEnemiesPos.push_back(std::make_pair(x, y));
	}

	input >> vectorSize;
	gameSave.shockEnemiesPos.clear();
	for (int i = 0; i < vectorSize; i++) {

		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("ShockEnemyPos is corrupted.\n");
		}
		gameSave.shockEnemiesPos.push_back(std::make_pair(x, y));
	}

	input >> vectorSize;
	gameSave.bombsPos.clear();
	for (int i = 0; i < vectorSize; i++) {

		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("BombPos is corrupted.\n");
		}
		gameSave.bombsPos.push_back(std::make_pair(x, y));
	}

	input >> vectorSize;
	gameSave.jumpsPos.clear();
	for (int i = 0; i < vectorSize; i++) {

		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("JumpPos is corrupted.\n");
		}
		gameSave.jumpsPos.push_back(std::make_pair(x, y));
	}

	input >> vectorSize;
	gameSave.healthPos.clear();
	for (int i = 0; i < vectorSize; i++) {

		input >> x >> y;
		if (x > gameSave.fieldWidth || x < 0 || y > gameSave.fieldHeight || y < 0) {
			throw LoadException("HealthPos is corrupted.\n");
		}
		gameSave.healthPos.push_back(std::make_pair(x, y));
	}

	input >> gameSave.startPos.first >> gameSave.startPos.second;
	if (gameSave.startPos.first > gameSave.fieldWidth || gameSave.startPos.first < 0 || gameSave.startPos.second > gameSave.fieldHeight || gameSave.startPos.second < 0) {
		throw LoadException("StartPos is corrupted.\n");
	}

	input >> gameSave.finishPos.first >> gameSave.finishPos.second;
	if (gameSave.finishPos.first > gameSave.fieldWidth || gameSave.finishPos.first < 0 || gameSave.finishPos.second > gameSave.fieldHeight || gameSave.finishPos.second < 0) {
		throw LoadException("FinishPos is corrupted.\n");
	}

	input >> gameSave.placedDatacenters;
	input >> gameSave.datacenterPos.first >> gameSave.datacenterPos.second;
	if (gameSave.datacenterPos.first > gameSave.fieldWidth || gameSave.datacenterPos.first < 0 || gameSave.datacenterPos.second > gameSave.fieldHeight || gameSave.datacenterPos.second < 0) {
		throw LoadException("FinishPos is corrupted.\n");
	}
	
	gameSave.fieldMap = new int* [gameSave.fieldHeight];
	for (int y = 0; y < gameSave.fieldHeight; y++) {
		gameSave.fieldMap[y] = new int[gameSave.fieldWidth];
		for (int x = 0; x < gameSave.fieldWidth; x++) {
			input >> gameSave.fieldMap[y][x];
			if (gameSave.fieldMap[y][x] != 0 && gameSave.fieldMap[y][x] != -2) {
				throw LoadException("FieldMap is corrupted.\n");
			}
		}
	}

	return input;
}