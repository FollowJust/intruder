#include "LogString.h"


std::string LogString::logField(Field* fieldPointer) {
    std::ostringstream logStream;

    logStream << "Generated " << fieldPointer << '\n';
    return logStream.str();
}

std::string LogString::logPlayerPosition(Player* player) {
    std::ostringstream logStream;

    logStream << player << '\n';
    std::cout << logStream.str();
    return logStream.str();
}

std::string LogString::logEnemyPosition(Enemy<BeatPolicy>* enemy) {
    std::ostringstream logStream;

    logStream << enemy << '\n';
    std::cout << logStream.str();
    return logStream.str();
}

std::string LogString::logEnemyPosition(Enemy<RobPolicy>* enemy) {
    std::ostringstream logStream;

    logStream << enemy << '\n';
    std::cout << logStream.str();
    return logStream.str();
}

std::string LogString::logEnemyPosition(Enemy<ShockPolicy>* enemy) {
    std::ostringstream logStream;

    logStream << enemy << '\n';
    std::cout << logStream.str();
    return logStream.str();
}

std::string LogString::logInventory(Player* player) {
    std::ostringstream logStream;

    logStream << *player << '\n';
    return logStream.str();
}

std::string LogString::logItemSet(Item* itemGot, int x, int y) {
    std::ostringstream logStream;

    logStream << "Set " << itemGot << " at X: " << x << " Y: " << y << '\n';
    return logStream.str();
}

std::string LogString::logItemGot(Player* player, Item* itemGot) {
    std::ostringstream logStream;

    logStream << "Got " << itemGot << " at X: " << player->getX() << " Y: " << player->getY() << '\n';
    return logStream.str();
}

std::string LogString::logItemUsed(Player* player, const char* itemName, bool isUsed) {
    std::ostringstream logStream;
    if (isUsed) {
        logStream << "Used " << itemName << " at X: " << player->getX() << " Y: " << player->getY() << '\n';
    }
    else {
        logStream << "Tried to use " << itemName << ", but there isn't any\n";
    }

    return logStream.str();
}

std::string LogString::logBombDetonated(int x, int y) {
    std::ostringstream logStream;

    logStream << "Bomb detonated at X: " << x << " Y: " << y << '\n';
    return logStream.str();
}

std::string LogString::logCellDestroyed(int x, int y) {
    std::ostringstream logStream;

    logStream << "Cell destroyed at X: " << x << " Y: " << y << '\n';
    return logStream.str();
}

std::string LogString::logDatacenterSet(int x, int y) {
    std::ostringstream logStream;

    logStream << "Datacenter set at X: " << x << " Y: " << y << '\n';
    return logStream.str();
}

std::string LogString::logDatacenterDestroyed(int x, int y) {
    std::ostringstream logStream;

    logStream << "Datacenter destroyed at X: " << x << " Y: " << y << '\n';
    return logStream.str();
}

std::string LogString::logAllDatacentersDown() {
    std::ostringstream logStream;

    logStream << "All Datacenters are down\n";
    return logStream.str();
}