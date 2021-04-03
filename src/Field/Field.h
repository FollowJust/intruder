#ifndef FIELD_H
#define FIELD_H


#include<iostream>
#include<queue>
#include"../Cell/Cell.h"
#include"../Utils/FieldUtility.h"

class Field
{

private:
    int fieldHeight, fieldWidth;
    static Field* fieldInstance;

    Cell** cells = nullptr;
    std::pair<int, int> startCell;
    std::pair<int, int> finishCell;

    Field() = default;
    Field(const Field& otherField);
	Field(Field&& otherField);

    Field& operator=(const Field& otherField);
	Field& operator=(Field&& otherField);

    void Initiate(int height, int width);
    void Destroy();

public:
    static Field* getInstance();
    void setParams(int height, int width);

    Cell& getCellAt(int x, int y) { return cells[x][y]; };

    int getHeight() { return fieldHeight; };
    int getWidth() { return fieldWidth; };

    bool checkCellWalkable(int x, int y) { return cells[x][y].isWalkable(); };

    bool checkCellItemSet(int x, int y) { return cells[x][y].isOccupiedByItem(); };
    Item* getCellItem(int x, int y) { return cells[x][y].getItem(); };
    void destroyCellItem(int x, int y);
    void setItem(Item* newItem, int x, int y);

    bool checkPlayerSet(int x, int y) { return cells[x][y].isOccupiedByPlayer(); };
    Player* getPlayer(int x, int y) { return cells[x][y].getPlayer(); };
    void placePlayer(Player* player, int x, int y);
    void movePlayer(Player* player, int x, int y);

    bool checkEnemySet(int x, int y) { return cells[x][y].isOccupiedByEnemy(); };
    Enemy<BeatPolicy>* getBeatEnemy(int x, int y) { return cells[x][y].getBeatEnemy(); };
    Enemy<RobPolicy>* getRobEnemy(int x, int y) { return cells[x][y].getRobEnemy(); };
    Enemy<ShockPolicy>* getShockEnemy(int x, int y) { return cells[x][y].getShockEnemy(); };
    void placeEnemy(Enemy<BeatPolicy>* enemy, int x, int y);
    void placeEnemy(Enemy<RobPolicy>* enemy, int x, int y);
    void placeEnemy(Enemy<ShockPolicy>* enemy, int x, int y);
    void moveEnemy(Enemy<BeatPolicy>* enemy, int x, int y);
    void moveEnemy(Enemy<RobPolicy>* enemy, int x, int y);
    void moveEnemy(Enemy<ShockPolicy>* enemy, int x, int y);

    void plantBomb(int x, int y);
    void triggerBomb(int x, int y);
    void detonateBomb(int x, int y);

    bool checkDatacenterSet(int x, int y) { return cells[x][y].isOccupiedByDatacenter(); };
    void placeDatacenter(int x, int y);
    void detonateDatacenter(int x, int y);

    std::pair<int, int> getStartCell() { return startCell; };
    std::pair<int, int> getFinishCell() { return finishCell; };
    void setStartCell(int x, int y) { startCell.first = x; startCell.second = y; };
    void setFinishCell(int x, int y) { finishCell.first = x; finishCell.second = y; };


    friend std::ostream& operator<<(std::ostream& out, Field const* field);

    ~Field();

    class Iterator{
    private:
        int iterX, iterY;
        Field* fieldPointer;
    public:
        Iterator(int x, int y);
        Iterator(const Iterator& otherIterator);

        Iterator& operator=(const Iterator& otherIterator);

        void setCoord(int x, int y);

        int getX() const { return iterX; };
        int getY() const { return iterY; };

        Cell& getCell() { return fieldPointer->cells[iterX][iterY]; };
        Cell& operator*() { return fieldPointer->cells[iterX][iterY]; };

        void next();
        void nextLine();
        void previous();
        void previousLine();

        bool isEndOfLine();

        Iterator& operator++();
        Iterator& operator--();
        Iterator operator++(int);
        Iterator operator--(int);

        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);
    };

    Iterator begin();
    Iterator end();
};

#endif
