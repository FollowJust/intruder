#ifndef CELL_H
#define CELL_H

#include "../Items/Item.h"
#include "../Characters/Player.h"
#include "../Characters/Enemy.h"
#include "..\Characters\Policies\Policy.h"
#include "..\Characters\Policies\BeatPolicy.h"
#include "..\Characters\Policies\RobPolicy.h"
#include "..\Characters\Policies\ShockPolicy.h"

enum class CellType{
    PASS,
    WALL,
    START,
    FINISH,
    BOMBPLANTED,
    DATACENTER
};

enum class EnemyType {
    BEAT,
    ROB,
    SHOCK
};

class Cell{
private:
    bool isCellWalkable;
    bool isStartCell, isFinishCell;
    bool isPlayerSet;
    bool isEnemySet;
    bool isItemSet;
    bool isBombPlanted;
    bool isDatacenterPlaced;
    CellType type;
    EnemyType enemyType;

    Player* player = nullptr;
    Enemy<BeatPolicy>* beatEnemy = nullptr;
    Enemy<RobPolicy>* robEnemy = nullptr;
    Enemy<ShockPolicy>* shockEnemy = nullptr;
    Item* item = nullptr;
public:
    Cell(){
        isCellWalkable = true;
        isStartCell = false;
        isFinishCell = false;
        isPlayerSet = false;
        isEnemySet = false;
        isItemSet = false;
        isBombPlanted = false;
        isDatacenterPlaced = false;
        type = CellType::PASS;
    }
    ~Cell();
    bool isWalkable(){ return isCellWalkable; };
    void setWalkable(bool isWalkable);

    void setType(CellType newType);
    CellType getType(){ return type; };

    void placePlayer(Player* player);
    void removePlayer();
    bool isOccupiedByPlayer() { return isPlayerSet; };
    Player* getPlayer() { return player; };

    void placeEnemy(Enemy<BeatPolicy>* enemy);
    void placeEnemy(Enemy<RobPolicy>* enemy);
    void placeEnemy(Enemy<ShockPolicy>* enemy);
    void removeEnemy();
    bool isOccupiedByEnemy() { return isEnemySet; };
    EnemyType getEnemyType() { return enemyType; };
    Enemy<BeatPolicy>* getBeatEnemy() { return beatEnemy; };
    Enemy<RobPolicy>* getRobEnemy() { return robEnemy; };
    Enemy<ShockPolicy>* getShockEnemy() { return shockEnemy; };

    void setItem(Item* newItem);
    bool isOccupiedByItem() { return isItemSet; };
    Item* getItem(){ return item; };
    void deleteItem();

    void plantBomb();
    void triggerBomb();
    void detonateBomb();
    bool isOccupiedByBomb() { return isBombPlanted; };

    void placeDatacenter();
    void destroyDatacenter();
    bool isOccupiedByDatacenter() { return isDatacenterPlaced; };
};
#endif
