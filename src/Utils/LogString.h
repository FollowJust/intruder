#ifndef LOG_STRING_H
#define LOG_STRING_H

#include <string>
#include <sstream>

#include "../Field/Field.h"
#include "../Characters/Enemy.h"
#include "../Characters/Player.h"
#include "../Characters/Policies/BeatPolicy.h"
#include "../Characters/Policies/RobPolicy.h"
#include "../Characters/Policies/ShockPolicy.h"
#include "../Items/Item.h"

class LogString {
public:
    std::string logField(Field* fieldPointer);
    std::string logPlayerPosition(Player* player);
    std::string logEnemyPosition(Enemy<BeatPolicy>* enemy);
    std::string logEnemyPosition(Enemy<RobPolicy>* enemy);
    std::string logEnemyPosition(Enemy<ShockPolicy>* enemy);
    std::string logInventory(Player* player);
    std::string logCellDestroyed(int x, int y);
    std::string logDatacenterSet(int x, int y);
    std::string logDatacenterDestroyed(int x, int y);
    std::string logAllDatacentersDown();
    std::string logItemSet(Item* itemSet, int x, int y);
    std::string logItemGot(Player* player, Item* itemGot);
    std::string logItemUsed(Player* player, const char* itemName, bool isUsed);
    std::string logBombDetonated(int x, int y);
};

#endif