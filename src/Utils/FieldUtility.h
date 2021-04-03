#ifndef FIELD_UTILITY_H
#define FIELD_UTILITY_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "../Cell/Cell.h"


class FieldUtility{
public:

    Cell** setLabyrinth(unsigned int fieldHeight, unsigned int fieldWidth);

    void printField(Cell** tmpCells, unsigned int linesAmount, unsigned int lineWidth);

    void printFieldASCII(std::vector<std::vector<int>> labyrinth, unsigned int lineWidth);

    int getCellsHeight(){ return tmpCellsHeight; };

    int getCellsWidth(){ return tmpCellsWidth; };

    std::pair<int, int> getStartCell() { return startCell; };
    std::pair<int, int> getFinishCell() { return finishCell; };

private:

    int tmpCellsHeight;
    int tmpCellsWidth;

    std::pair<int, int> startCell;
    std::pair<int, int> finishCell;

    bool randomBool();

    int randomInt(int MaxInt);

    std::vector<std::vector<int>> generateLabyrinth(unsigned int fieldHeight, unsigned int fieldWidth);

    std::vector<int> generateLabyrinthLine(unsigned int fieldWidth);

    std::vector<int> generateNextLabyrinthLine(std::vector<int> previousLabyrinthLine, unsigned int fieldWidth);

    std::vector<int> generateLastLabyrinthLine(std::vector<int> previousLabyrinthLine, unsigned int fieldWidth);

    void printFieldLine(Cell* tmpCellsLine, unsigned int lineWidth, bool withDebug);

    void printFieldLineASCII(std::vector<int> labyrinthLine, unsigned int fieldWidth, bool withDebug);

};
#endif
