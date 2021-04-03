#include "FieldUtility.h"


    Cell** FieldUtility::setLabyrinth(unsigned int fieldHeight, unsigned int fieldWidth){
        srand(time(0));
        std::vector<std::vector<int>> labyrinth = this->generateLabyrinth(fieldHeight, fieldWidth);

        tmpCellsHeight = fieldHeight * 2;
        tmpCellsWidth = fieldWidth * 2;
        Cell** tmpCells = new Cell*[tmpCellsHeight];
        for (int i = 0; i < tmpCellsHeight; i++)
        {
            tmpCells[i] = new Cell[tmpCellsWidth];
        }

        int cellLineIndex = 0;
        //this->printFieldASCII(labyrinth, fieldWidth);
        for(unsigned int i = 0; i < fieldHeight; i++){
            for(unsigned int j = 0; j < fieldWidth * 2; j++){
                switch (labyrinth[i][j]) {
                    case 0:
                        if(j == fieldWidth * 2 - 1 && tmpCells[cellLineIndex][j - 1].isWalkable()){
                            tmpCells[cellLineIndex][j].setWalkable(false);
                            tmpCells[cellLineIndex][j].setType(CellType::WALL);
                        }
                        else{
                            tmpCells[cellLineIndex][j].setWalkable(true);
                            tmpCells[cellLineIndex][j].setType(CellType::PASS);
                        }
                        if(((j > 0) && (labyrinth[i][j - 1] == -2)) || ((j < fieldWidth * 2 - 1) && (labyrinth[i][j + 1] == -2)) || ((i < labyrinth.size() - 1) && (labyrinth[i + 1][j] == -1))  || ((i > 0) && (labyrinth[i - 1][j] == -1))){
                            tmpCells[cellLineIndex + 1][j].setWalkable(false);
                            tmpCells[cellLineIndex + 1][j].setType(CellType::WALL);
                        }
                        else{
                            tmpCells[cellLineIndex + 1][j].setWalkable(true);
                            tmpCells[cellLineIndex + 1][j].setType(CellType::PASS);
                        }

                        break;
                    case -1:
                        tmpCells[cellLineIndex][j].setWalkable(false);
                        tmpCells[cellLineIndex][j].setType(CellType::WALL);

                        tmpCells[cellLineIndex + 1][j].setWalkable(false);
                        tmpCells[cellLineIndex + 1][j].setType(CellType::WALL);
                        break;
                    case -2:
                        tmpCells[cellLineIndex][j].setWalkable(true);
                        tmpCells[cellLineIndex][j].setType(CellType::PASS);

                        tmpCells[cellLineIndex + 1][j].setWalkable(false);
                        tmpCells[cellLineIndex + 1][j].setType(CellType::WALL);
                        break;
                    default:
                        tmpCells[cellLineIndex][j].setWalkable(true);
                        tmpCells[cellLineIndex][j].setType(CellType::PASS);
                        break;
                }
            }
            cellLineIndex += 2;
        }

        int randomCoord = rand() % tmpCellsWidth;
        while (tmpCells[randomCoord][0].getType() == CellType::WALL) {
            randomCoord = rand() % tmpCellsWidth;
        }
        tmpCells[randomCoord][0].setWalkable(true);
        tmpCells[randomCoord][0].setType(CellType::START);
        startCell = std::make_pair(randomCoord, 0);

        randomCoord = rand() % tmpCellsWidth;
        while (tmpCells[randomCoord][tmpCellsHeight - 2].getType() == CellType::WALL) {
            randomCoord = rand() % tmpCellsWidth;
        }
        tmpCells[randomCoord][tmpCellsHeight - 2].setWalkable(true);
        tmpCells[randomCoord][tmpCellsHeight - 2].setType(CellType::FINISH);
        finishCell = std::make_pair(randomCoord, tmpCellsHeight - 2);

        //setLabyrinthBorders(tmpCells, tmpCellsHeight, tmpCellsWidth);
        //printField(tmpCells, tmpCellsHeight, tmpCellsWidth);

        return tmpCells;
    }

    void FieldUtility::printField(Cell** tmpCells, unsigned int linesAmount, unsigned int lineWidth){
        for(unsigned int i = 0; i < linesAmount; i++){
            printFieldLine(tmpCells[i], lineWidth, false);
        }
    }

    void FieldUtility::printFieldASCII(std::vector<std::vector<int>> labyrinth, unsigned int lineWidth){
        for(unsigned int i = 0; i < labyrinth.size(); i++){
            printFieldLineASCII(labyrinth[i], lineWidth * 2, false);
        }
    }





    bool FieldUtility::randomBool(){
        int random = rand() % 20 + 1;
        return random % 2;
    }

    int FieldUtility::randomInt(int MaxInt){
        return rand() % MaxInt;
    }

    std::vector<std::vector<int>> FieldUtility::generateLabyrinth(unsigned int fieldHeight, unsigned int fieldWidth){

        std::vector<std::vector<int>> labyrinth;
        std::vector<int> firstLine = generateLabyrinthLine(fieldWidth);
        labyrinth.push_back(firstLine);
        //printLabyrinthLine(firstLine, fieldWidth, false);
        std::vector<int> nextLine = firstLine;
        for(unsigned int i = 0; i < fieldHeight - 2; i++){
            nextLine = generateNextLabyrinthLine(nextLine, fieldWidth);
            labyrinth.push_back(nextLine);
            //printLabyrinthLine(nextLine, fieldWidth, false);
        }
        nextLine = generateLastLabyrinthLine(nextLine, fieldWidth);
        labyrinth.push_back(nextLine);
        //printLabyrinthLine(nextLine, fieldWidth, false);
        return labyrinth;
    }

    std::vector<int> FieldUtility::generateLabyrinthLine(unsigned int fieldWidth){

        std::vector<int> labyrinthLine;

        int setAmount = 1;
        int setStartCellIndex;
        int setEndCellIndex;
        int notBlockedCellIndex = 0;
        for(unsigned int i = 0; i < fieldWidth * 2; i++){
            labyrinthLine.push_back(i + 1);
            labyrinthLine.push_back(0);
        }
        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){

            if(randomBool() == 1){

                labyrinthLine[i + 1] = -1;
                if(setAmount != 1){
                    setStartCellIndex = i - setAmount * 2 + 2;
                    setEndCellIndex = i;

                    notBlockedCellIndex = randomInt(setAmount) * 2;
                    notBlockedCellIndex += setStartCellIndex;

                    for(int j = setStartCellIndex; j < setEndCellIndex + 1; j+=2){
                        if(j != notBlockedCellIndex){
                            labyrinthLine[j] = -2;
                        }
                    }
                }
                setAmount = 1;
            }
            else{
                setAmount += 1;
                labyrinthLine[i + 2] = labyrinthLine[i];
            }
        }
        if(setAmount > 2){
            setStartCellIndex = fieldWidth * 2 - 2 - (setAmount - 1) * 2 + 2;
            setEndCellIndex = fieldWidth * 2 - 2;

            notBlockedCellIndex = randomInt(setAmount - 1) * 2;
            notBlockedCellIndex += setStartCellIndex;

            for(int i = setStartCellIndex; i < setEndCellIndex + 1; i += 2){

                if(i != notBlockedCellIndex){
                    labyrinthLine[i] = -2;
                }
            }
        }
        return labyrinthLine;
    }

    std::vector<int> FieldUtility::generateNextLabyrinthLine(std::vector<int> previousLabyrinthLine, unsigned int fieldWidth){

        std::vector<int> nextLabyrinthLine = previousLabyrinthLine;
        int freeIndex = 0;
        int setAmount = 1;
        int setStartCellIndex;
        int setEndCellIndex;
        int notBlockedCellIndex = 0;

        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){
            if(freeIndex < nextLabyrinthLine[i]){
                freeIndex = nextLabyrinthLine[i] + 1;
            }
        }
        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){
            if(nextLabyrinthLine[i] == -2){
                nextLabyrinthLine[i] = freeIndex;
            }
            else{
                freeIndex++;
            }
            nextLabyrinthLine[i + 1] = 0;
        }
        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){

            if(randomBool() == 1 || nextLabyrinthLine[i] == nextLabyrinthLine[i + 2]){

                nextLabyrinthLine[i + 1] = -1;
                if(setAmount != 1){
                    setStartCellIndex = i - setAmount * 2 + 2;
                    setEndCellIndex = i;

                    notBlockedCellIndex = randomInt(setAmount) * 2;
                    notBlockedCellIndex += setStartCellIndex;

                    for(int j = setStartCellIndex; j < setEndCellIndex + 1; j+=2){
                        if(j != notBlockedCellIndex){
                            nextLabyrinthLine[j] = -2;
                        }
                    }
                }
                setAmount = 1;
            }
            else{
                setAmount += 1;
                nextLabyrinthLine[i + 2] = nextLabyrinthLine[i];
            }
        }
        if(setAmount > 2){
            setStartCellIndex = fieldWidth * 2 - 2 - (setAmount - 1) * 2 + 2;
            setEndCellIndex = fieldWidth * 2 - 2;

            notBlockedCellIndex = randomInt(setAmount - 1) * 2;
            notBlockedCellIndex += setStartCellIndex;

            for(int i = setStartCellIndex; i < setEndCellIndex + 1; i += 2){

                if(i != notBlockedCellIndex){
                    nextLabyrinthLine[i] = -2;
                }
            }
        }
        return nextLabyrinthLine;
    }

    std::vector<int> FieldUtility::generateLastLabyrinthLine(std::vector<int> previousLabyrinthLine, unsigned int fieldWidth){

        std::vector<int> nextLabyrinthLine = previousLabyrinthLine;
        int freeIndex = 0;

        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){
            if(freeIndex < nextLabyrinthLine[i]){
                freeIndex = nextLabyrinthLine[i] + 1;
            }
        }
        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){
            if(nextLabyrinthLine[i] == -2){
                nextLabyrinthLine[i] = freeIndex;
            }
            else{
                freeIndex++;
            }
            nextLabyrinthLine[i + 1] = 0;
        }
        for(unsigned int i = 0; i < fieldWidth * 2; i += 2){

            if(nextLabyrinthLine[i] != nextLabyrinthLine[i + 2]){
                nextLabyrinthLine[i] = -2;
                nextLabyrinthLine[i + 2] = nextLabyrinthLine[i];
                if(i == fieldWidth * 2 - 2){
                    nextLabyrinthLine[i + 1] = -1;
                }
                else{
                    nextLabyrinthLine[i + 1] = 0;
                }

            }
            else{
                nextLabyrinthLine[i] = -2;
            }
        }
        return nextLabyrinthLine;
    }

    void FieldUtility::printFieldLine(Cell* tmpCellsLine, unsigned int lineWidth, bool withDebug){
        for(unsigned int i = 0; i < lineWidth; i++){
            switch (tmpCellsLine[i].isWalkable()) {
                case true:
                    std::cout << "   ";
                    break;
                case false:
                    std::cout << "XXX";
                    break;
            }
        }
        std::cout << "e\n";
    }

    void FieldUtility::printFieldLineASCII(std::vector<int> labyrinthLine, unsigned int fieldWidth, bool withDebug){
        if(withDebug){
            for(unsigned int i = 0; i < fieldWidth; i++){

                std::cout << labyrinthLine[i] << " ";
            }
            std::cout << '\n';
        }
        for(unsigned int i = 0; i < fieldWidth; i++){
            switch (labyrinthLine[i]) {
                case 0:
                    std::cout <<  " ";
                    break;
                case -1:
                    std::cout <<  "|";
                    break;
                case -2:
                    std::cout <<  "___";
                    break;
                default:
                    if(labyrinthLine[i] > 9){
                        if(withDebug){
                            std::cout << labyrinthLine[i] << " ";
                        }
                        else{
                            std::cout << "   ";
                        }
                    }
                    else{
                        if(withDebug){
                            std::cout << " " << labyrinthLine[i] << " ";
                        }
                        else{
                            std::cout << "   ";
                        }

                    }
                    break;
            }
        }
        std::cout << "E\n";
    }
