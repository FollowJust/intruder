#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "../Field/Field.h"
#include "../Characters/Creature.h"
#include "../Characters/Player.h"

#include "../Characters/Enemy.h"
#include "..\Characters\Policies\Policy.h"
#include "..\Characters\Policies\BeatPolicy.h"
#include "..\Characters\Policies\RobPolicy.h"
#include "..\Characters\Policies\ShockPolicy.h"

#include "../Items/ItemFactory.h"
#include "../Items/Bomb/BombFactory.h"
#include "../Items/Medkit/MedkitFactory.h"
#include "../Items/Jump/JumpFactory.h"
#include "../Items/Bomb/BombItem.h"
#include "../Items/Jump/JumpItem.h"
#include "../Items/Medkit/MedkitItem.h"

#include "../Display/Display.h"

#include "../Items/ItemInteraction/ItemInteraction.h"

#include "../Logs/EventPublisher/EventPublisher.h"
#include "../Logs/Logger/FileLogger.h"
#include "../Logs/Logger/ConsoleLogger.h"
#include "../Logs/LoggerImplementation/MoveLoggerImplementation.h"
#include "../Logs/LoggerImplementation/ItemLoggerImplementation.h"
#include "../Logs/LoggerImplementation/FieldLoggerImplementation.h"
#include "../Utils/LogString.h"


#include "../Utils/LeePathfinder.h"

#include "../TurnState/TurnState.h"
#include "../TurnState/PlayerTurn.h"
#include "../TurnState/EnemyTurn.h"

#include "../Save/Memento/Memento.h"
#include "../Save/Memento/GameMemento.h"

#include "../Exceptions/LoadException.h"
#include "../Exceptions/SaveException.h"

#include "SFML/Graphics.hpp"
#include <queue>
#include <random>
#include <string>
#include <sstream>

enum class GameState {
    Menu,
    Game,
    EndMenu
};

class GameManager {

private:

    int windowSizeX;
    int windowSizeY;
    int bottomMenuSizeY;

    Display* display;

    int rectSize;

    GameState currentState;

    const int maxMedkits = 10;
    const int maxJumps = 15;
    const int maxBombs = 20;

    const int maxBeatEnemies = 1;
    const int maxRobEnemies = 1;
    const int maxShockEnemies = 1;

    std::queue<std::pair<int, int>> datacentersDetonationQueue;
    int placedDatacenters = 0;
    const int maxDatacenters = 4;
    bool allDatacentersDown = false;


    Field* fieldPointer;
    Player* player;
    std::pair<int, int> spawnPlayerPosition;
    std::vector<Enemy<BeatPolicy>*> beatEnemyVector;
    std::vector<Enemy<RobPolicy>*> robEnemyVector;
    std::vector<Enemy<ShockPolicy>*> shockEnemyVector;

    TurnState* turnState;

    ItemInteraction* itemInteraction;

    std::queue<std::pair<int, int>> detonationQueue;
    std::queue<sf::Time> detonationTimer;
    const int bombDetonationTime = 2; //in seconds

    EventPublisher eventPublisher;
    LogFile* logFile;

    Logger* fieldLogger;
    Logger* playerMoveLogger;
    Logger* itemLogger;

    LogString logString;

    sf::Clock clock;

    std::pair<int, int> randomCell();

    void setDatacenter();
    void checkDatacenters();

    std::pair<int, int> getCurrentDatacenter() { return datacentersDetonationQueue.front(); };
    int getDatacentersQueueLength() { return datacentersDetonationQueue.size(); };

    void setItems();
    void setEnemies();

    

    bool isPossibleToMove(int x, int y);
    bool isPossibleToMoveEnemy(int x, int y);
    void checkAndMove(int x, int y);


    bool checkEnd();

    bool checkItem(int x, int y);
    void getItem(int x, int y);

    void addBombToDetonationQueue(int x, int y);
    void setBombTimer();
    void updateBombTimer();
    void detonateBomb();

    
    void savePlayer(GameSave& gameSave);
    void saveEnemies(GameSave& gameSave);
    void saveField(GameSave& gameSave);

    void loadPlayer(GameSave& gameSave);
    void loadEnemies(GameSave& gameSave);
    void loadField(GameSave& gameSave);

public:
    GameManager(int fieldSizeX, int fieldSizeY, int bottomMenuSizeY, int rectSize);
    ~GameManager();

    void startMenu();

    void startGame();

    void endGame();

    void setState(GameState newState) { currentState = newState; };

    void setTurnState(TurnState* newTurnState) { turnState = newTurnState; };

    void draw(sf::RenderWindow& window);

    Player* getPlayer() { return player; };
    
    std::pair<int, int> getDatacenterCoords() { return datacentersDetonationQueue.back(); };

    void move(int deltaX, int deltaY) { turnState->move(deltaX, deltaY); };
    void movePlayer(int deltaX, int deltaY) { checkAndMove(deltaX, deltaY); };
    void moveEnemies();

    void updateState();

    void playerUseJumpItem();
    void playerUseBombItem();

    void useJumpItem() { turnState->useJumpItem(); };
    void useBombItem() { turnState->useBombItem(); };

    bool checkGameOver() { return checkEnd(); };


    Memento* saveGame();
    void loadGame(Memento* newGameSave);
};

#endif
