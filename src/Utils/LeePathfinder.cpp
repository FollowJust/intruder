#include "LeePathfinder.h"

LeePathfinder::LeePathfinder(){
	field = Field::getInstance();
    fieldHeight = field->getHeight();
    fieldWidth = field->getWidth();
    waveValue = 1;
    generateFieldMap();
}

void LeePathfinder::generateFieldMap() {
    fieldMap = new int* [fieldWidth];
    for (int coordX = 0; coordX < fieldWidth; coordX++) {
        fieldMap[coordX] = new int[fieldHeight];
        for (int coordY = 0; coordY < fieldHeight; coordY++) {
            if (field->checkCellWalkable(coordX, coordY) || field->checkEnemySet(coordX, coordY) || field->checkPlayerSet(coordX, coordY)) {
                fieldMap[coordX][coordY] = -1;
            }
            else {
                fieldMap[coordX][coordY] = -2;
            }
        }
    }
}

void LeePathfinder::printPath() {
    for (int coordY = 0; coordY < fieldHeight; coordY++) {
        for (int coordX = 0; coordX < fieldWidth; coordX++) {
            switch (fieldMap[coordX][coordY]) {
            case -1:
                std::cout << ". ";
                break;
            case -2:
                std::cout << "# ";
                break;
            case 0:
                std::cout << "S ";
                break;
            case -3:
                std::cout << "E ";
                break;
            default:
                std::cout << "+ ";
            }
        }
        std::cout << "\n";
    }
}

void LeePathfinder::waveExpanse(int startX, int startY, int endX, int endY) {
    generateFieldMap();
    bool foundEnd = false;
    int curValue = 0;
    fieldMap[startX][startY] = 0;
    fieldMap[endX][endY] = -3;
    while (!foundEnd){
        bool foundEmpty = false;
        for (int x = 0; x < fieldWidth && !foundEnd; ++x)
        {
            for (int y = 0; y < fieldHeight; ++y)
            {
                if (fieldMap[x][y] == curValue)
                {
                    // check east cell
                    if (x < fieldWidth - 1)
                    {
                        int& east = fieldMap[x + 1][y];
                        if (east == -3)
                        {
                            east = curValue + 1;
                            foundEnd = true;
                            break;
                        }
                        else if (east == -1)
                        {
                            east = curValue + 1;
                            foundEmpty = true;
                        }
                    }

                    // check west cell
                    if (x > 0)
                    {
                        int& west = fieldMap[x - 1][y];
                        if (west == -3)
                        {
                            west = curValue + 1;
                            foundEnd = true;
                            break;
                        }
                        else if (west == -1)
                        {
                            west = curValue + 1;
                            foundEmpty = true;
                        }
                    }

                    // check south cell
                    if (y < fieldHeight - 1)
                    {
                        int& south = fieldMap[x][y + 1];
                        if (south == -3)
                        {
                            south = curValue + 1;
                            foundEnd = true;
                            break;
                        }
                        else if (south == -1)
                        {
                            south = curValue + 1;
                            foundEmpty = true;
                        }
                    }

                    // check north cell
                    if (y > 0)
                    {
                        int& north = fieldMap[x][y - 1];
                        if (north == -3)
                        {
                            north = curValue + 1;
                            foundEnd = true;
                            break;
                        }
                        else if (north == -1)
                        {
                            north = curValue + 1;
                            foundEmpty = true;
                        }
                    }
                }
            }
        }

        if (!foundEnd && !foundEmpty)
        {
            break;
        }

        curValue++;
    }


}


std::pair<int, int> LeePathfinder::getStep(int curX, int curY, int startX, int startY) {


    while (curX != startX || curY != startY) {
        bool isMoved = false;
        
        for (int deltaX = -1; deltaX <= 1 && !isMoved; deltaX++) {
            for (int deltaY = -1; deltaY <= 1 && !isMoved; deltaY++) {

                if (abs(deltaX) + abs(deltaY) != 1 || curX + deltaX > fieldWidth || curY + deltaY > fieldHeight || curX + deltaX < 0 || curY + deltaY < 0) {
                    continue;
                }

                if (fieldMap[curX + deltaX][curY + deltaY] < 0) {
                    continue;
                }
                
                if (fieldMap[curX + deltaX][curY + deltaY] == fieldMap[curX][curY] - 1) {
                    curX += deltaX;
                    curY += deltaY;

                    lastStep = std::make_pair(deltaX * -1, deltaY * -1);

                    isMoved = true;
                    break;
                }
            }
        }
    }
    //std::cout << "step is: " << lastStep.first << " " << lastStep.second << '\n';
    return lastStep;
}


LeePathfinder::~LeePathfinder() {
    for (int i = 0; i < fieldHeight; i++) {
        delete[] fieldMap[i];
    }
    delete[] fieldMap;
}
