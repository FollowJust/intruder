#include "Cell.h"

void Cell::setType(CellType newType){
    type = newType;
    if (this->type == CellType::START) {
        isStartCell = true;
    }
    else if (this->type == CellType::FINISH) {
        isFinishCell = true;
    }
}

void Cell::setWalkable(bool isCellWalkable){
    this->isCellWalkable = isCellWalkable;
    if(isCellWalkable){
        setType(CellType::PASS);
    }
    else{
        setType(CellType::WALL);
    }
}

void Cell::placePlayer(Player* player) {
    isCellWalkable = false;
    isPlayerSet = true;
    this->player = player;
}

void Cell::removePlayer() {
    isCellWalkable = true;
    isPlayerSet = false;
    this->player = nullptr;
}

void Cell::placeEnemy(Enemy<BeatPolicy>* enemy) {
    isCellWalkable = false;
    isEnemySet = true;
    enemyType = EnemyType::BEAT;
    this->beatEnemy = enemy;
}

void Cell::placeEnemy(Enemy<RobPolicy>* enemy) {
    isCellWalkable = false;
    isEnemySet = true;
    enemyType = EnemyType::ROB;
    this->robEnemy = enemy;
}

void Cell::placeEnemy(Enemy<ShockPolicy>* enemy) {
    isCellWalkable = false;
    isEnemySet = true;
    enemyType = EnemyType::SHOCK;
    this->shockEnemy = enemy;
}

void Cell::removeEnemy() {
    isCellWalkable = true;
    isEnemySet = false;
    this->beatEnemy = nullptr;
    this->robEnemy = nullptr;
    this->shockEnemy = nullptr;
}

void Cell::setItem(Item* newItem){
    isItemSet = true;
    this->item = newItem;
}

void Cell::deleteItem(){
    isItemSet = false;
    if(!item){
        return;
    }
    delete item;
    item = nullptr;
}

void Cell::plantBomb() {
    type = CellType::BOMBPLANTED;
    isBombPlanted = true;
}

void Cell::triggerBomb() {
    if (isStartCell) {
        type = CellType::START;
    }
    else if (isFinishCell) {
        type = CellType::FINISH;
    }
    else {
        type = CellType::PASS;
    }
    isBombPlanted = false;
}

void Cell::detonateBomb() {
    if (type == CellType::WALL) {
        setType(CellType::PASS);
        setWalkable(true);
    }
}

void Cell::placeDatacenter() {
    type = CellType::DATACENTER;
    isDatacenterPlaced = true;
}

void Cell::destroyDatacenter() {
    type = CellType::PASS;
    isDatacenterPlaced = false;
}


Cell::~Cell() {
    deleteItem();
}