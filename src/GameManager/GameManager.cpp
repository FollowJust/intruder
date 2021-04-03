#include "GameManager.h"

GameManager::GameManager(int windowSizeX, int windowSizeY, int bottomMenuSizeY, int rectSize)
{

    this->windowSizeX = windowSizeX;
    this->windowSizeY = windowSizeY;
    this->bottomMenuSizeY = bottomMenuSizeY;
    this->rectSize = rectSize;

    display = new Display(this->windowSizeX, this->windowSizeY, this->bottomMenuSizeY, this->rectSize);

    logFile = new LogFile("logs.txt");
    
    int fieldSizeX = this->windowSizeX / this->rectSize + 1;
    int fieldSizeY = this->windowSizeX / this->rectSize + 1;

    fieldLogger = new FileLogger(new FieldLoggerImplementation(),logFile);

    eventPublisher.subscribe(UpdateEvent::FieldGenerated, fieldLogger);

    fieldPointer = Field::getInstance();
    fieldPointer->setParams(fieldSizeX, fieldSizeY);

    eventPublisher.notify(UpdateEvent::FieldGenerated, logString.logField(fieldPointer));
    
    spawnPlayerPosition = fieldPointer->getStartCell();

    player = new Player(std::get<0>(spawnPlayerPosition), std::get<1>(spawnPlayerPosition));
    
    turnState = new PlayerTurn(this);

    itemInteraction = new ItemInteraction();
}

GameManager::~GameManager() {
    if (player) {
        delete player;
    }
    if (turnState) {
        delete turnState;
    }
    if (itemInteraction) {
        delete itemInteraction;
    }
    if (fieldPointer) {
        delete fieldPointer;
    }
    if (logFile) {
        delete logFile;
    }
    if (fieldLogger) {
        delete fieldLogger;
    }
    if (playerMoveLogger) {
        delete playerMoveLogger;
    }
    if (itemLogger) {
        delete itemLogger;
    }
    if (display) {
        delete display;
    } 
}

void GameManager::updateState() {
    updateBombTimer();
    checkDatacenters();
}
void GameManager::startGame() {
    this->setState(GameState::Game);
    bool gameEnd = false;
    eventPublisher.subscribe(UpdateEvent::ItemSet, fieldLogger);
    eventPublisher.subscribe(UpdateEvent::EnemySet, fieldLogger);
    eventPublisher.subscribe(UpdateEvent::DatacenterSet, fieldLogger);

    setItems();
    setEnemies();
    setDatacenter();

    fieldPointer->placePlayer(player, player->getX(), player->getY());

    playerMoveLogger = new FileLogger(new MoveLoggerImplementation(), logFile);
    itemLogger = new FileLogger(new ItemLoggerImplementation(), logFile);

    eventPublisher.subscribe(UpdateEvent::PlayerMoved, playerMoveLogger);
    eventPublisher.subscribe(UpdateEvent::EnemyMoved, playerMoveLogger);

    eventPublisher.subscribe(UpdateEvent::ItemGot, itemLogger);
    eventPublisher.subscribe(UpdateEvent::ItemUsed, itemLogger);
    eventPublisher.subscribe(UpdateEvent::InventoryChanged, itemLogger);
    eventPublisher.subscribe(UpdateEvent::EnemyAction, itemLogger);

    eventPublisher.subscribe(UpdateEvent::BombDetonated, fieldLogger);
    eventPublisher.subscribe(UpdateEvent::CellDestroyed, fieldLogger);
    eventPublisher.subscribe(UpdateEvent::DatacenterDestroyed, fieldLogger);
    eventPublisher.subscribe(UpdateEvent::AllDatacentersDown, fieldLogger);
}

void GameManager::startMenu() {
    this->setState(GameState::Menu);
}

void GameManager::endGame() {
    this->setState(GameState::EndMenu);
}
void GameManager::draw(sf::RenderWindow& gameWindow) {
    switch (currentState)
    {
    case GameState::Menu:
        display->drawStartMenu(gameWindow);
        break;
    case GameState::Game:
        display->drawGame(gameWindow, player);
        break;
    case GameState::EndMenu:
        display->drawEndMenu(gameWindow);
        break;
    default:
        break;
    }
}


bool GameManager::checkEnd() {
    int x = player->getX();
    int y = player->getY();
    if (x == std::get<0>(fieldPointer->getFinishCell()) && y == std::get<1>(fieldPointer->getFinishCell())) {
        if (allDatacentersDown) {
            return true;
        }
        else {
            return false;
        }
    }
    if (player->getHP() <= 0) {
        return true;
    }
    return false;
}


void GameManager::playerUseBombItem() {

    if (player->getAmountBombs() > 0) {
        player->placeBomb();
        int x = player->getX();
        int y = player->getY();
        fieldPointer->plantBomb(x, y);
        addBombToDetonationQueue(x, y);
        setBombTimer();
        std::cout << "The bomb has been planted\n";

        eventPublisher.notify(UpdateEvent::ItemUsed, logString.logItemUsed(player, "BombItem", true));
        eventPublisher.notify(UpdateEvent::InventoryChanged, logString.logInventory(player));
    }
    else {
        eventPublisher.notify(UpdateEvent::ItemUsed, logString.logItemUsed(player, "BombItem", false));
    }
}

void GameManager::playerUseJumpItem() {
    if (player->getAmountJumps() > 0) {
        player->useJump();
        eventPublisher.notify(UpdateEvent::ItemUsed, logString.logItemUsed(player, "JumpItem", true));
        eventPublisher.notify(UpdateEvent::InventoryChanged, logString.logInventory(player));
    }
    else {
        std::cout << "No jumps\n";
        eventPublisher.notify(UpdateEvent::ItemUsed, logString.logItemUsed(player, "JumpItem", false));
    }
}

void GameManager::getItem(int x, int y) {
    if (checkItem(player->getX(), player->getY())) {


        Item* itemToInteractWith = fieldPointer->getCellItem(player->getX(), player->getY());

        std::cout << "Got " << itemToInteractWith << " at X: " << player->getX() << " Y: " << player->getY() << '\n';
        eventPublisher.notify(UpdateEvent::ItemGot, logString.logItemGot(player, itemToInteractWith));

        itemInteraction->setStrategy(new TakeEverythingStrategy());
        itemInteraction->setItem(itemToInteractWith);
        itemInteraction->useStrategy(player);

        std::cout << *player << '\n';
        eventPublisher.notify(UpdateEvent::InventoryChanged, logString.logInventory(player));
        fieldPointer->destroyCellItem(player->getX(), player->getY());

    }
}

void GameManager::addBombToDetonationQueue(int x, int y) {
    detonationQueue.push(std::make_pair(x, y));
}

void GameManager::setBombTimer() {
    detonationTimer.push(clock.getElapsedTime());
}

void GameManager::updateBombTimer() {
    sf::Time time;
    for (int i = 0; i < detonationTimer.size(); i++) {
        time = detonationTimer.front();
        detonationTimer.pop();

        if (clock.getElapsedTime() > time + sf::seconds(bombDetonationTime)) {
            detonateBomb();
        }
        else {
            detonationTimer.push(time);
        }

    }
}

void GameManager::detonateBomb() {
    std::pair<int, int> bomb = detonationQueue.front();
    int x = std::get<0>(bomb);
    int y = std::get<1>(bomb);

    detonationQueue.pop();
    eventPublisher.notify(UpdateEvent::BombDetonated, logString.logBombDetonated(x, y));

    fieldPointer->triggerBomb(x, y);
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (x + i >= 0 && x + i < fieldPointer->getWidth() - 1 && y + j >= 0 && y + j < fieldPointer->getHeight() - 1) {
                if (datacentersDetonationQueue.size() > 0 && x + i == std::get<0>(datacentersDetonationQueue.front()) && y + j == std::get<1>(datacentersDetonationQueue.front())) {
                    datacentersDetonationQueue.pop();
                    fieldPointer->detonateDatacenter(x + i, y + j);
                    eventPublisher.notify(UpdateEvent::DatacenterDestroyed, logString.logDatacenterDestroyed(x + i, y + j));
                }
                fieldPointer->detonateBomb(x + i, y + j);
                eventPublisher.notify(UpdateEvent::CellDestroyed, logString.logCellDestroyed(x + i, y + j));
            }
        }
    }
}


bool GameManager::isPossibleToMove(int x, int y)
{
    if (x > fieldPointer->getWidth() - 1 || x < 0) {
        return false;
    }
    if (y > fieldPointer->getHeight() - 1 || y < 0) {
        return false;
    }
    if (!fieldPointer->checkCellWalkable(x, y)) {
        if (player->getCanSkipWalls()) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return true;
    }
}

bool GameManager::isPossibleToMoveEnemy(int x, int y) {
    if (x > fieldPointer->getWidth() - 1 || x < 0) {
        return false;
    }
    if (y > fieldPointer->getHeight() - 1 || y < 0) {
        return false;
    }
    if (!fieldPointer->checkCellWalkable(x, y) && !fieldPointer->checkEnemySet(x, y) && !fieldPointer->checkPlayerSet(x, y)) {
        return false;
    }
    else {
        return true;
    }
}

void GameManager::moveEnemies() {
    int playerX = player->getX();
    int playerY = player->getY();

    bool defendDatacenter = false;

    std::pair<int, int> datacenterCoords;
    if (!allDatacentersDown) {
        datacenterCoords = getDatacenterCoords();
        if (sqrt(pow(playerX - datacenterCoords.first, 2) + pow(playerY - datacenterCoords.second, 2)) < 3) {
            defendDatacenter = true;
        }
    }
    LeePathfinder* leePathfinder = new LeePathfinder();
    
    for (auto beatEnemy : beatEnemyVector) {
        int enemyX = beatEnemy->getX();
        int enemyY = beatEnemy->getY();

        leePathfinder->waveExpanse(enemyX, enemyY, playerX, playerY);
        std::pair<int, int> moveCoords = leePathfinder->getStep(playerX, playerY, enemyX, enemyY);
        if (isPossibleToMoveEnemy(beatEnemy->getX() + moveCoords.first, beatEnemy->getY() + moveCoords.second)) {
            fieldPointer->moveEnemy(beatEnemy, moveCoords.first, moveCoords.second);
            eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(beatEnemy));
        }
    }
    
    if (!defendDatacenter) {

        for (auto robEnemy : robEnemyVector) {
            int enemyX = robEnemy->getX();
            int enemyY = robEnemy->getY();
            if (sqrt(pow(playerX - enemyX, 2) + pow(playerY - enemyY, 2)) < sqrt(pow(datacenterCoords.first - enemyX, 2) + pow(datacenterCoords.second - enemyY, 2))) { //считать по путb
                leePathfinder->waveExpanse(enemyX, enemyY, playerX, playerY);
                std::pair<int, int> moveCoords = leePathfinder->getStep(playerX, playerY, enemyX, enemyY);
                if (isPossibleToMoveEnemy(robEnemy->getX() + moveCoords.first, robEnemy->getY() + moveCoords.second)) {
                    fieldPointer->moveEnemy(robEnemy, moveCoords.first, moveCoords.second);
                    eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(robEnemy));
                }
            }
            else {
                leePathfinder->waveExpanse(enemyX, enemyY, datacenterCoords.first, datacenterCoords.second);
                std::pair<int, int> moveCoords = leePathfinder->getStep(datacenterCoords.first, datacenterCoords.second, enemyX, enemyY);
                if (isPossibleToMoveEnemy(robEnemy->getX() + moveCoords.first, robEnemy->getY() + moveCoords.second)) {
                    fieldPointer->moveEnemy(robEnemy, moveCoords.first, moveCoords.second);
                    eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(robEnemy));
                }
            }
        }

        for (auto shockEnemy : shockEnemyVector) {
            int enemyX = shockEnemy->getX();
            int enemyY = shockEnemy->getY();
            if (sqrt(pow(playerX - enemyX, 2) + pow(playerY - enemyY, 2)) < sqrt(pow(datacenterCoords.first - enemyX, 2) + pow(datacenterCoords.second - enemyY, 2))) { //считать по путb
                leePathfinder->waveExpanse(enemyX, enemyY, playerX, playerY);
                std::pair<int, int> moveCoords = leePathfinder->getStep(playerX, playerY, enemyX, enemyY);
                if (isPossibleToMoveEnemy(shockEnemy->getX() + moveCoords.first, shockEnemy->getY() + moveCoords.second)) {
                    fieldPointer->moveEnemy(shockEnemy, moveCoords.first, moveCoords.second);
                    eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(shockEnemy));
                }
            }
            else {
                leePathfinder->waveExpanse(enemyX, enemyY, datacenterCoords.first, datacenterCoords.second);
                std::pair<int, int> moveCoords = leePathfinder->getStep(datacenterCoords.first, datacenterCoords.second, enemyX, enemyY);
                if (isPossibleToMoveEnemy(shockEnemy->getX() + moveCoords.first, shockEnemy->getY() + moveCoords.second)) {
                    fieldPointer->moveEnemy(shockEnemy, moveCoords.first, moveCoords.second);
                    eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(shockEnemy));
                }
            }
        }
    }
    else {

        for (auto robEnemy : robEnemyVector) {
            int enemyX = robEnemy->getX();
            int enemyY = robEnemy->getY();

            leePathfinder->waveExpanse(enemyX, enemyY, datacenterCoords.first, datacenterCoords.second);
            std::pair<int, int> moveCoords = leePathfinder->getStep(datacenterCoords.first, datacenterCoords.second, enemyX, enemyY);
            if (isPossibleToMoveEnemy(robEnemy->getX() + moveCoords.first, robEnemy->getY() + moveCoords.second)) {
                fieldPointer->moveEnemy(robEnemy, moveCoords.first, moveCoords.second);
                eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(robEnemy));
            }
        }
        for (auto shockEnemy : shockEnemyVector) {
            int enemyX = shockEnemy->getX();
            int enemyY = shockEnemy->getY();

            leePathfinder->waveExpanse(enemyX, enemyY, datacenterCoords.first, datacenterCoords.second);
            std::pair<int, int> moveCoords = leePathfinder->getStep(datacenterCoords.first, datacenterCoords.second, enemyX, enemyY);
            if (isPossibleToMoveEnemy(shockEnemy->getX() + moveCoords.first, shockEnemy->getY() + moveCoords.second)) {
                fieldPointer->moveEnemy(shockEnemy, moveCoords.first, moveCoords.second);
                eventPublisher.notify(UpdateEvent::EnemyMoved, logString.logEnemyPosition(shockEnemy));
            }
        }
    }

    delete leePathfinder;
    delete turnState;
    setTurnState(new PlayerTurn(this));
}


void GameManager::checkAndMove(int x, int y) {
    if (player->getShocked()) {
        player->setIsShocked(false);
        setTurnState(new EnemyTurn(this));
        return;
    }
    if (isPossibleToMove(player->getX() + x, player->getY() + y)) {
        if (player->getCanSkipWalls()) {
            if (!fieldPointer->checkCellWalkable(player->getX() + x, player->getY() + y) && fieldPointer->checkCellWalkable(player->getX() + x * 2, player->getY() + y * 2)) {
                player->jumped();
                x *= 2;
                y *= 2;
                fieldPointer->movePlayer(player, x, y);
            }
            else {
                player->jumped();
                player->addJump();
                std::cout << "Can't jump there, mate\n";
            }
        }
        else {
            fieldPointer->movePlayer(player, x, y);
        }
    }
    else {
        std::cout << "Can't move there, mate\n";
    }
    eventPublisher.notify(UpdateEvent::PlayerMoved, logString.logPlayerPosition(player));
    delete turnState;
    setTurnState(new EnemyTurn(this));
    if (!checkEnd()) {

        getItem(player->getX(), player->getY());
    }
    turnState->move(0, 0);
}

bool GameManager::checkItem(int x, int y) {
    return fieldPointer->checkCellItemSet(x, y);
}

void GameManager::setItems() {
    ItemFactory* itemFactory;
    std::pair<int, int> cellCoord;

    itemFactory = new MedkitFactory();
    for(int placedMedkits = 0; placedMedkits < maxMedkits; placedMedkits++){
        cellCoord = randomCell();
        Item* tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord));
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord)));
    }
    delete itemFactory;
    itemFactory = new BombFactory();
    for (int placedBombs = 0; placedBombs < maxBombs; placedBombs++) {
        cellCoord = randomCell();
        Item* tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord));
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord)));
    }
    delete itemFactory;
    itemFactory = new JumpFactory();
    for (int placedJumps = 0; placedJumps < maxJumps; placedJumps++) {
        cellCoord = randomCell();
        Item* tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord));
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, std::get<0>(cellCoord), std::get<1>(cellCoord)));
    }
    delete itemFactory;
}

void GameManager::setEnemies() {

    std::pair<int, int> cellCoord;
    int enemyId = 0;

    for (int placedBeatEnemies = 0; placedBeatEnemies < maxBeatEnemies; placedBeatEnemies++) {
        cellCoord = randomCell();
        Enemy<BeatPolicy>* tmpEnemy = new Enemy<BeatPolicy>(cellCoord.first, cellCoord.second, enemyId);
        fieldPointer->placeEnemy(tmpEnemy, cellCoord.first, cellCoord.second);
        beatEnemyVector.push_back(tmpEnemy);
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(tmpEnemy));
        enemyId++;
    }

    for (int placedRobEnemies = 0; placedRobEnemies < maxRobEnemies; placedRobEnemies++) {
        cellCoord = randomCell();
        Enemy<RobPolicy>* tmpEnemy = new Enemy<RobPolicy>(cellCoord.first, cellCoord.second, enemyId);
        fieldPointer->placeEnemy(tmpEnemy, cellCoord.first, cellCoord.second);
        robEnemyVector.push_back(tmpEnemy);
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(tmpEnemy));
        enemyId++;
    }

    for (int placedShockEnemies = 0; placedShockEnemies < maxShockEnemies; placedShockEnemies++) {
        cellCoord = randomCell();
        Enemy<ShockPolicy>* tmpEnemy = new Enemy<ShockPolicy>(cellCoord.first, cellCoord.second, enemyId);
        fieldPointer->placeEnemy(tmpEnemy, cellCoord.first, cellCoord.second);
        shockEnemyVector.push_back(tmpEnemy);
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(tmpEnemy));
        enemyId++;
    }
}

void GameManager::setDatacenter() {
    std::pair<int, int> cellCoord;
    cellCoord = randomCell();    
    datacentersDetonationQueue.push(cellCoord);
    fieldPointer->placeDatacenter(std::get<0>(cellCoord), std::get<1>(cellCoord));
    placedDatacenters++;
}

void GameManager::checkDatacenters() {
    if (allDatacentersDown) {
        return;
    }
    if (getDatacentersQueueLength() == 0) {
        if (placedDatacenters < maxDatacenters) {
            setDatacenter();
        }
        else {
            allDatacentersDown = true;
            eventPublisher.notify(UpdateEvent::AllDatacentersDown, logString.logAllDatacentersDown());
        }
    }
}


std::pair<int, int> GameManager::randomCell() {
    int x = rand() % fieldPointer->getHeight();
    int y = rand() % fieldPointer->getWidth();

    while(!fieldPointer->checkCellWalkable(x, y)) {
        x = rand() % fieldPointer->getHeight();
        y = rand() % fieldPointer->getWidth();
    }
    return std::make_pair(x, y);
}

Memento* GameManager::saveGame() {
    GameSave gameSave;
    savePlayer(gameSave);
    saveEnemies(gameSave);
    saveField(gameSave);
    std::cout << gameSave.startPos.first << " " << gameSave.startPos.second << "\n";
    std::cout << gameSave.fieldHeight << " " << gameSave.fieldWidth << "\n";
    
    return new GameMemento(gameSave);
}

void GameManager::savePlayer(GameSave& gameSave) {
    gameSave.playerPos = std::make_pair(player->getX(), player->getY());
    gameSave.playerHealth = player->getHP();
    gameSave.playerAmountBombs = player->getAmountBombs();
    gameSave.playerAmountJumps = player->getAmountJumps();
    gameSave.playerCanSkipWalls = player->getCanSkipWalls();
    gameSave.playerIsShocked = player->getShocked();
}

void GameManager::saveEnemies(GameSave& gameSave) {
    for (auto beatEnemy : beatEnemyVector) {
        gameSave.beatEnemiesPos.push_back(std::make_pair(beatEnemy->getX(), beatEnemy->getY()));
    }

    for (auto robEnemy : robEnemyVector) {
        gameSave.robEnemiesPos.push_back(std::make_pair(robEnemy->getX(), robEnemy->getY()));
    }

    for (auto shockEnemy : shockEnemyVector) {
        gameSave.shockEnemiesPos.push_back(std::make_pair(shockEnemy->getX(), shockEnemy->getY()));
    }
}

void GameManager::saveField(GameSave& gameSave) {
    if (detonationQueue.size() != 0) {
        throw SaveException();
    }

    gameSave.fieldHeight = fieldPointer->getHeight();
    gameSave.fieldWidth = fieldPointer->getWidth();
    gameSave.placedDatacenters = placedDatacenters;

    gameSave.fieldMap = new int*[gameSave.fieldHeight];

    for (int y = 0; y < fieldPointer->getHeight(); y++) {
        gameSave.fieldMap[y] = new int[gameSave.fieldWidth];
        for (int x = 0; x < fieldPointer->getWidth(); x++) {
            switch (fieldPointer->getCellAt(x, y).getType()) {

            case CellType::WALL:
                gameSave.fieldMap[y][x] = -2;
                break;

            case CellType::PASS:
                gameSave.fieldMap[y][x] = 0;
                break;

            case CellType::START:
                gameSave.startPos = std::make_pair(x, y);
                gameSave.fieldMap[y][x] = 0;
                break;

            case CellType::FINISH:
                gameSave.finishPos = std::make_pair(x, y);
                gameSave.fieldMap[y][x] = 0;
                break;

            case CellType::DATACENTER:
                if (getDatacentersQueueLength() != 0)
                    gameSave.datacenterPos = getDatacenterCoords();
                gameSave.fieldMap[y][x] = 0;
                break;

            default:
                break;
            }

            if (fieldPointer->getCellAt(x, y).isOccupiedByItem()) {
                switch (fieldPointer->getCellItem(x, y)->getIndex()) {
                case 0:
                    gameSave.healthPos.push_back(std::make_pair(x, y));
                    break;

                case 1:
                    gameSave.jumpsPos.push_back(std::make_pair(x, y));
                    break;

                case 2:
                    gameSave.bombsPos.push_back(std::make_pair(x, y));
                    break;

                default:
                    break;
                }
            }
        }
    }

}


void GameManager::loadGame(Memento* newGameSave) {
    GameSave gameSave = newGameSave->getState();
    loadField(gameSave);
    loadEnemies(gameSave);
    loadPlayer(gameSave);

}

void GameManager::loadPlayer(GameSave& gameSave) {
    fieldPointer->movePlayer(player, gameSave.playerPos.first - player->getX(), gameSave.playerPos.second - player->getY());
    player->setHP(gameSave.playerHealth);
    player->setAmountBombs(gameSave.playerAmountBombs);
    player->setAmountJumps(gameSave.playerAmountJumps);
    player->setCanSkipWalls(gameSave.playerCanSkipWalls);
    player->setIsShocked(gameSave.playerIsShocked);
}

void GameManager::loadEnemies(GameSave& gameSave) {
    if (beatEnemyVector.size() != gameSave.beatEnemiesPos.size() || robEnemyVector.size() != gameSave.robEnemiesPos.size() || shockEnemyVector.size() != gameSave.shockEnemiesPos.size()) {
        throw LoadException();
    }

    for (int i = 0; i < beatEnemyVector.size(); i++) {
        fieldPointer->moveEnemy(beatEnemyVector[i], gameSave.beatEnemiesPos[i].first - beatEnemyVector[i]->getX(), gameSave.beatEnemiesPos[i].second - beatEnemyVector[i]->getY());
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(beatEnemyVector[i]));
    }

    for (int i = 0; i < robEnemyVector.size(); i++) {
        fieldPointer->moveEnemy(robEnemyVector[i], gameSave.robEnemiesPos[i].first - robEnemyVector[i]->getX(), gameSave.robEnemiesPos[i].second - robEnemyVector[i]->getY());
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(robEnemyVector[i]));
    }

    for (int i = 0; i < shockEnemyVector.size(); i++) {
        fieldPointer->moveEnemy(shockEnemyVector[i], gameSave.shockEnemiesPos[i].first - shockEnemyVector[i]->getX(),gameSave.shockEnemiesPos[i].second - shockEnemyVector[i]->getY());
        eventPublisher.notify(UpdateEvent::EnemySet, logString.logEnemyPosition(shockEnemyVector[i]));
    }
}

void GameManager::loadField(GameSave& gameSave) {
    if (fieldPointer->getHeight() != gameSave.fieldHeight || fieldPointer->getWidth() != gameSave.fieldWidth) {
        throw LoadException();
    }
    this->placedDatacenters = gameSave.placedDatacenters;

    for (int y = 0; y < fieldPointer->getHeight(); y++) {
        for (int x = 0; x < fieldPointer->getWidth(); x++) {
            switch (gameSave.fieldMap[y][x]) {

            case -2:
                fieldPointer->getCellAt(x, y).setType(CellType::WALL);
                fieldPointer->getCellAt(x, y).setWalkable(false);
                break;

            case 0:
                fieldPointer->getCellAt(x, y).setWalkable(true);
                if (x == gameSave.startPos.first && y == gameSave.startPos.second) {
                    fieldPointer->setStartCell(x, y);
                    fieldPointer->getCellAt(x, y).setType(CellType::START);
                }
                else if (x == gameSave.finishPos.first && y == gameSave.finishPos.second) {
                    fieldPointer->setFinishCell(x, y);
                    fieldPointer->getCellAt(x, y).setType(CellType::FINISH);
                }
                else if (x == gameSave.datacenterPos.first && y == gameSave.datacenterPos.second) {
                    if (getDatacentersQueueLength() != 0) {
                        fieldPointer->detonateDatacenter(datacentersDetonationQueue.front().first, datacentersDetonationQueue.front().second);
                        datacentersDetonationQueue.front() = gameSave.datacenterPos;
                        fieldPointer->placeDatacenter(x, y);
                    }
                    else {
                        allDatacentersDown = false;
                        datacentersDetonationQueue.push(gameSave.datacenterPos);
                        fieldPointer->placeDatacenter(x, y);
                    }
                    eventPublisher.notify(UpdateEvent::DatacenterSet, logString.logDatacenterSet(gameSave.datacenterPos.first, gameSave.datacenterPos.second));
                }
                else {
                    fieldPointer->getCellAt(x, y).setType(CellType::PASS);
                }
                break;
            default:
                break;
            }

            if (fieldPointer->checkCellItemSet(x, y)) {
                fieldPointer->destroyCellItem(x, y);
            }
        }
        
    }

    ItemFactory* itemFactory = new MedkitFactory();
    for (auto position : gameSave.healthPos) {
        Item* tmpItem = fieldPointer->getCellAt(position.first, position.second).getItem();
        if (tmpItem) {
            delete tmpItem;
        }
        tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, position.first, position.second);
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, position.first, position.second));
    }
    delete itemFactory;

    itemFactory = new BombFactory();
    for (auto position : gameSave.bombsPos) {
        Item* tmpItem = fieldPointer->getCellAt(position.first, position.second).getItem();
        if (tmpItem) {
            delete tmpItem;
        }
        tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, position.first, position.second);
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, position.first, position.second));
    }
    delete itemFactory;

    itemFactory = new JumpFactory();
    for (auto position : gameSave.jumpsPos) {
        Item* tmpItem = fieldPointer->getCellAt(position.first, position.second).getItem();
        if (tmpItem) {
            delete tmpItem;
        }
        tmpItem = itemFactory->createItem();
        fieldPointer->setItem(tmpItem, position.first, position.second);
        eventPublisher.notify(UpdateEvent::ItemSet, logString.logItemSet(tmpItem, position.first, position.second));
    }
    delete itemFactory;
}