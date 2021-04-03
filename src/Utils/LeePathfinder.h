#ifndef LEE_PATHFINDER_H
#define LEE_PATHFINDER_H

#include <vector>
#include <array>

#include "../Field/Field.h"

class LeePathfinder{
	Field* field;

	int** fieldMap;

	int waveValue;
	int fieldHeight, fieldWidth;

	std::pair<int, int> lastStep;


public:
	LeePathfinder();

	void generateFieldMap();

	void waveExpanse(int curX, int curY, int endX, int endY);

	std::pair<int, int> getStep(int curX, int curY, int startX, int startY);

	void printPath();

	~LeePathfinder();
};

#endif // LEE_PATHFINDER_H