#ifndef TAKE_EVERYTHING_STRATEGY_H
#define TAKE_EVERYTHING_STRATEGY_H

#include "InteractionStrategy.h"

class TakeEverythingStrategy : public InteractionStrategy {
public:
    void use(Player* player, Item* item);
};

#endif
