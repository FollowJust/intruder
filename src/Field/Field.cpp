#include "Field.h"

Field* Field::fieldInstance = nullptr;

Field::Field(const Field& otherField) {
    this->fieldHeight = otherField.fieldHeight;
    this->fieldWidth = otherField.fieldWidth;

    this->cells = new Cell * [this->fieldHeight];
    for (int i = 0; i < this->fieldHeight; i++)
    {
        this->cells[i] = new Cell[this->fieldWidth];
        for (int j = 0; j < this->fieldWidth; j++)
        {
            this->cells[i][j] = otherField.cells[i][j];
        }
    }
}

Field::Field(Field&& otherField) {
    this->fieldHeight = otherField.fieldHeight;
    this->fieldWidth = otherField.fieldWidth;

    this->cells = otherField.cells;
    otherField.cells = nullptr;
}

Field& Field::operator=(const Field& otherField)
{
    if (&otherField == this)
        return *this;

    Destroy();

    this->fieldHeight = otherField.fieldHeight;
    this->fieldWidth = otherField.fieldWidth;

    this->cells = new Cell * [this->fieldHeight];
    for (int i = 0; i < this->fieldHeight; i++)
    {
        this->cells[i] = new Cell[this->fieldWidth];
        for (int j = 0; j < this->fieldWidth; j++)
        {
            this->cells[i][j] = otherField.cells[i][j];
        }
    }

    return *this;
}

Field& Field::operator=(Field&& otherField) {

    Destroy();
    this->fieldHeight = otherField.fieldHeight;
    this->fieldWidth = otherField.fieldWidth;

    this->cells = otherField.cells;
    otherField.cells = nullptr;

    return *this;
}

void Field::Initiate(int height, int width) {
    FieldUtility* tmpUtility = new FieldUtility();
    cells = tmpUtility->setLabyrinth(height / 2, width / 2);
    fieldHeight = tmpUtility->getCellsHeight();
    fieldWidth = tmpUtility->getCellsHeight();
    startCell = tmpUtility->getStartCell();
    finishCell = tmpUtility->getFinishCell();
    //tmpUtility->printField(cells, fieldHeight, fieldWidth);
    delete tmpUtility;
}

void Field::destroyCellItem(int x, int y) {
    cells[x][y].deleteItem();
}

void Field::setItem(Item* newItem, int x, int y) {
    cells[x][y].setItem(newItem);
}

void Field::placePlayer(Player* player, int x, int y) {
    cells[x][y].placePlayer(player);
}

void Field::movePlayer(Player* player, int x, int y) {
    cells[player->getX()][player->getY()].removePlayer();
    player->move(x, y);
    placePlayer(player, player->getX(), player->getY());
}

void Field::placeEnemy(Enemy<BeatPolicy>* enemy, int x, int y) {
    cells[x][y].placeEnemy(enemy);
}

void Field::placeEnemy(Enemy<RobPolicy>* enemy, int x, int y) {
    cells[x][y].placeEnemy(enemy);
}

void Field::placeEnemy(Enemy<ShockPolicy>* enemy, int x, int y) {
    cells[x][y].placeEnemy(enemy);
}

void Field::moveEnemy(Enemy<BeatPolicy>* enemy, int x, int y) {
    cells[enemy->getX()][enemy->getY()].removeEnemy();
    enemy->move(x, y);
    placeEnemy(enemy, enemy->getX(), enemy->getY());
    enemy->action();
}

void Field::moveEnemy(Enemy<RobPolicy>* enemy, int x, int y) {
    cells[enemy->getX()][enemy->getY()].removeEnemy();
    enemy->move(x, y);
    placeEnemy(enemy, enemy->getX(), enemy->getY());
    enemy->action();
}

void Field::moveEnemy(Enemy<ShockPolicy>* enemy, int x, int y) {
    cells[enemy->getX()][enemy->getY()].removeEnemy();
    enemy->move(x, y);
    placeEnemy(enemy, enemy->getX(), enemy->getY());
    enemy->action();
}


void Field::plantBomb(int x, int y) {
    cells[x][y].plantBomb();
}

void Field::triggerBomb(int x, int y) {
    cells[x][y].triggerBomb();
}

void Field::detonateBomb(int x, int y) {
    cells[x][y].detonateBomb();
}

void Field::placeDatacenter(int x, int y) {
    cells[x][y].placeDatacenter();
}

void Field::detonateDatacenter(int x, int y) {
    cells[x][y].destroyDatacenter();
}

void Field::Destroy() {
    if (cells){
        for (int i = 0; i < fieldHeight; i++)
        {
            delete cells[i];
        }
        delete[] cells;
    }
}

Field::~Field() {
    //delete fieldInstance;
    Destroy();
}

void Field::setParams(int height, int width) {
    if (!cells){
        if(height > 1 && width > 1){
            Initiate(height, width);
        }
        else{
            throw std::invalid_argument("Height and Width must be greater than 1");
        }
    }
    else {
        std::cout << "You've already set the parameters for the field" << '\n';
    }
}

Field* Field::getInstance() {
    if (fieldInstance == nullptr) {
        fieldInstance = new Field;
    }
    return fieldInstance;
}

Field::Iterator::Iterator(int x, int y){
    fieldPointer = Field::getInstance();
    if(x < 0 || y < 0 || x > fieldPointer->fieldWidth - 1 || y > fieldPointer->fieldHeight){
        throw std::invalid_argument("Wrong coordinates at Field::Iterator");
    }
    iterX = x;
    iterY = y;
}

Field::Iterator::Iterator(const Iterator& otherIterator){
    fieldPointer = otherIterator.fieldPointer;
    iterX = otherIterator.iterX;
    iterY = otherIterator.iterY;
}

Field::Iterator& Field::Iterator::operator=(const Iterator& otherIterator){
    if(this == &otherIterator){
        return *this;
    }
    this->iterX = otherIterator.iterX;
    this->iterY = otherIterator.iterY;
    this->fieldPointer = otherIterator.fieldPointer;

    return *this;
}

void Field::Iterator::setCoord(int x, int y){
    if(x < 0 || y < 0 || x > fieldPointer->fieldWidth - 1 || y > fieldPointer->fieldHeight){
        throw std::invalid_argument("Wrong coordinates at Field::Iterator");
    }
    iterX = x;
    iterY = y;
}

void Field::Iterator::next(){
    if(iterX == 0 && iterY == fieldPointer->fieldHeight){
        throw std::out_of_range("Trying to set Field::Iterator out of array");
    }
    else if(iterX == fieldPointer->fieldWidth - 1){
        iterX = 0;
        iterY++;
    }
    else{
        iterX++;
    }
}

void Field::Iterator::nextLine(){
    if(iterY == fieldPointer->fieldHeight - 1){
        throw std::out_of_range("Trying to set Field::Iterator out of array");
    }
    else{
        iterY++;
    }
}

void Field::Iterator::previous(){
    if(iterX == 0 && iterY == 0){
        throw std::out_of_range("Trying to set Field::Iterator out of array");
    }
    else if(iterX == 0){
        iterX = fieldPointer->fieldWidth - 1;
        iterY--;
    }
    else{
        iterX--;
    }
}

void Field::Iterator::previousLine(){
    if(iterY == 0){
        throw std::out_of_range("Trying to set Field::Iterator out of array");
    }
    else{
        iterY--;
    }
}

bool Field::Iterator::isEndOfLine(){
    return iterX == fieldPointer->fieldWidth - 1;
}

Field::Iterator& Field::Iterator::operator++(){
    next();
    return *this;
}

Field::Iterator& Field::Iterator::operator--(){
    previous();
    return *this;
}

Field::Iterator Field::Iterator::operator++(int){
    Iterator newIterator = *this;
    this->next();
    return newIterator;
}

Field::Iterator Field::Iterator::operator--(int){
    Iterator newIterator = *this;
    this->previous();
    return newIterator;
}


bool Field::Iterator::operator==(const Iterator& other){
    return this->iterX == other.iterX && this->iterY == other.iterY && this->fieldPointer == other.fieldPointer;
}

bool Field::Iterator::operator!=(const Iterator& other){
    return !(*this == other);
}

Field::Iterator Field::begin(){
    return Iterator(0, 0);
}

Field::Iterator Field::end(){
    return Iterator(0, fieldHeight);
}


std::ostream& operator<<(std::ostream& out, Field const* field) {
    out << "Field: ";
    out << "Height: " << field->fieldHeight << " Width: " << field->fieldWidth;

    return out;
}